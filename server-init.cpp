#undef UNICODE

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WALL_H

#define WIN32_LEAN_AND_MEAN

#include "SendMail.h"

#include <vector>
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <chrono>
#include <time.h>
#include <string>



#include "DB.h"
#include "RequestFactory.h"


#define BUFFER_SIZE 1024


#pragma comment (lib, "Ws2_32.lib")



int __cdecl main(void)
{
    DB::getInstance();
    vector<SOCKET*> CLIENTS;

    WSADATA wsaData;
    int wsaErr;
    int port = 2002;

    SOCKET serverSocket = INVALID_SOCKET;
    SOCKET acceptSocket = INVALID_SOCKET;

    WORD wVersionRequested = MAKEWORD(2, 2);

    //dll setup
    wsaErr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaErr != 0) {
        std::cout << "The Winsock dll not found!" << endl;
        return 1;
    }
    else
    {
        std::cout << "The Winsock dll found!" << endl;
        std::cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    //server socket setup
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "socket() is OK!" << endl;
    }

    //binding
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, "0.0.0.0", &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (::bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) ==SOCKET_ERROR) {
        std::cout << "BIND() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;

    }
    else {
        std::cout << "bind is OK!\n";
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
    }
    else {
        std::cout << "listen() is OK, waiting for connections..." << endl;
    }

    SOCKET activeSockets[FD_SETSIZE]{0};

    // Adăugare socket de ascultare în lista de socketuri active.
    activeSockets[0] = serverSocket;



    int i=0, result=0;
    SOCKET currentSocket=INVALID_SOCKET;
    fd_set readSet;
    FD_ZERO(&readSet);

    int emailsSent = -1;

    while (TRUE) {
       
        for (i = 0; i < FD_SETSIZE; i++)
        {
            currentSocket = activeSockets[i];
            if (currentSocket != 0)
            {
                FD_SET(currentSocket, &readSet);
            }
        }

        result = select(0, &readSet, NULL, NULL, NULL);
        if (result == SOCKET_ERROR)
        {
            printf("select a esuat: %ld\n", WSAGetLastError());
            break;
        }

        for (i = 0; i < FD_SETSIZE; i++)
        {
            currentSocket = activeSockets[i];
            if (FD_ISSET(currentSocket, &readSet))
            {
                if (currentSocket == serverSocket)
                {
                    // Un client nou se încearcă să se conecteze.
                    struct sockaddr_in clientAddr = { 0 };
                    clientAddr.sin_family = AF_INET;
                    clientAddr.sin_port = htons(port);
                    int clientAddrSize = sizeof(clientAddr);
                    SOCKET newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
                    if (newSocket == INVALID_SOCKET)
                    {
                        printf("accept a esuat: %ld\n", WSAGetLastError());
                    }
                    else
                    {
                        printf("Client conectat: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                        for (i = 1; i < FD_SETSIZE; i++)
                        {
                            if (activeSockets[i] == 0)
                            {
                                activeSockets[i] = newSocket;
                                break;
                            }
                        }
                    }
                }
                else {

                    // Un client existent trimite date.
                    char buffer[BUFFER_SIZE]="\n";
                    int bytesReceived = recv(currentSocket, buffer, BUFFER_SIZE, 0);
                    if (bytesReceived <= 0)
                    {
                        // Clientul a închis conexiunea sau a apărut o eroare.
                        printf("Client deconectat.\n");
                        shutdown(currentSocket,2);
                        activeSockets[i] = 0;
                    }
                    else
                    {
                        // Procesare date primite.
                        std::cout << "----------------NEW REQUEST----------------" << endl;
                        std::cout << "Received data : " << buffer << endl;
                        
                        IRequest* request = RequestFactory::getRequest(buffer);
                        request->makeRequest();
                        
                        //Trimite raspunsul catre client.
                        send(currentSocket, request->sendResponse().c_str(), request->sendResponse().length(), 0);
                        std::cout << "Sent data : " << request->sendResponse()<<endl;

                    }
                }
            }
        }
        
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        ltm->tm_mon = 1 + ltm->tm_mon;
        ltm->tm_year = 1900 + ltm->tm_year;
        if (ltm->tm_hour == 1)
            emailsSent = -1;//in fiecare noapte la ora 1 se reintinitializeaza aceasta variabila
        if (emailsSent == -1) {

            if (ltm->tm_hour == 17) {
                std::vector<int> tomorrowLessons;
                tomorrowLessons = DB::getInstance()->getTomorrowLessons(ltm);
                for (auto i = tomorrowLessons.begin(); i < tomorrowLessons.end(); i++)
                {
                    SendMail* mail = new SendMail(*i);
                    mail->initializeData();
                    mail->send();
                    delete mail;
                }
                emailsSent = 1;
            }
        }
        
        
    }
    closesocket(serverSocket);
    for (i = 0; i < FD_SETSIZE; i++)
    {
        currentSocket = activeSockets[i];
        if (currentSocket != 0)
        {
            closesocket(currentSocket);
        }
    }

    // Dezactivare Winsock, deconectarea de la baza de date.
    DB::getInstance()->disconnect();
    WSACleanup();

    return 0;
}