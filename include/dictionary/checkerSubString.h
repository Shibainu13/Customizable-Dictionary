#pragma once

#include <string>

const int maxSize = 100005;

class checker{
public:
    checker();

    bool checkSubString(std::string subSt, std::string st);

private:
    int z[maxSize];
};