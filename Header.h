#pragma once
#include <string>
#include <vector>

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

}
