#pragma once
//#include "tinyxml2.h"
#include <string>
#include <map>
#include <vector>

class Strings{

    private:
        std::map<std::string, std::string> strings;
        std::map<std::string, std::vector<std::string>> responses;
        std::map<std::string, std::vector<std::string>> preferences;
        std::vector<std::string> tierList;
        std::vector<std::string> keys;

    public:
        Strings();
        void loadStrings();
        std::string getString(std::string key);
        std::string getResponse(std::string key);
        std::string getTier(int rank);
        std::string getPreference(std::string key, int color);
        std::string getKey(int key);

};