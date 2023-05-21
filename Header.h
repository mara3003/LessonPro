#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <nanodbc/nanodbc.h>

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

    tm stringToDateTime(string data) {

        tm dateTime;
        dateTime.tm_year = stoi(data.substr(0, 4));
        dateTime.tm_mon = stoi(data.substr(5, 2)); 
        dateTime.tm_mday = stoi(data.substr(8,2));
        dateTime.tm_hour = stoi(data.substr(11, 2));
        dateTime.tm_min = stoi(data.substr(15,2));
        
        return dateTime;
    }

    std::string VectorToString(std::vector<std::string> V) {
        std::string str;
        for (auto i = V.begin(); i < V.end(); i++)
        {
            str = str + "/" + *i;
        }
        return str;
    }

    std::string deleteBlank(std::string &str) {
        int i = 0;
        for (i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ')
                break;
        }
        str = str.substr(0, i);
        return str;
    }
}
