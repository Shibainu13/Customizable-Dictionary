#ifndef UTILITY_SAVE_HPP
#define UTILITY_SAVE_HPP

#include <UserSession.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <chrono>

class UtilitySave
{
public:
    static bool CreateDirectoryRecursive(const std::string &dirName, std::error_code &err);
    static void DeleteDirContent(const std::string &dirPath);
    static bool sortDir(const std::string &filenameA, const std::string &filenameB);
    static std::string getCurrentDateTime();
    static std::string calculateTimeDifference(const std::string &logoutTime);
};

#endif