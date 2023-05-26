#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <nanodbc/nanodbc.h>
#include <comutil.h>
#include <Windows.h>
#include <fstream>
#include "JournalActions.h"

using namespace std;

namespace {


    vector<string> myStrtok(string data) {
        vector<string> details;
        char delim = '/';
        int num = 0;
        string word = "";
        for (int i = 0; i < (int)data.size(); i++) {
            if (data[i] != delim) {
                //word = data[i];
                word.push_back(data[i]);
            }
            else {
                details.push_back(word);
                word = "";
                //num = 0;
            }
        }
        details.push_back(word);
        return details;
    }

    vector<string> myStrtok2(string data) {
        vector<string> details;
        char delim = ' ';
        int num = 0;
        string word = "";
        for (int i = 0; i < (int)data.size(); i++) {
            if (data[i] != delim) {
                //word = data[i];
                word.push_back(data[i]);
            }
            else {
                details.push_back(word);
                word = "";
                //num = 0;
            }
        }
        details.push_back(word);
        return details;
    }


    std::string VectorToString(std::vector<std::string> V) {
        std::string str;
        for (auto i = V.begin(); i < V.end(); i++)
        {
            str = str + "/" + *i;
        }
        return str;
    }

    std::string my_deleteBlank(std::string &str) {
        int i = 0;
        for (i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ')
                break;
        }
        str = str.substr(0, i);
        return str;
    }

    void writeActionsFile(JournalActions* action) {
        time_t now = time(0);
        char* dt=ctime(&now);
        string eroare(dt);
        eroare += " : ";
        eroare += action->printAction();
        ofstream file;
        file.open("ActionsJournal.txt", ios_base::app);
        file << eroare;
        file.close();
        
    }

    
}
