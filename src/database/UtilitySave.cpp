#include <UtilitySave.hpp>

bool UtilitySave::CreateDirectoryRecursive(const std::string &dirName, std::error_code &err)
{
    err.clear();
    if (!std::filesystem::create_directories(dirName, err))
    {
        if (std::filesystem::exists(dirName))
        {
            // The folder already exists:
            err.clear();
            return true;
        }
        return false;
    }
    return true;
}

bool UtilitySave::sortDir(const std::string &filenameA, const std::string &filenameB)
{
    int a = std::stoi(filenameA.substr(1, 2));
    int b = std::stoi(filenameB.substr(1, 2));
    return (a < b);
}

void UtilitySave::DeleteDirContent(const std::string &dirPath)
{
    if (std::filesystem::exists(dirPath))
    {
        for (const auto &entry : std::filesystem::directory_iterator(dirPath))
            std::filesystem::remove_all(entry.path());
        std::filesystem::remove(dirPath);
    }
    else
    {
        std::cerr << dirPath + "not found.\n";
    }
}

std::string UtilitySave::getCurrentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), UserData::LOGOUT_TIME_FORMAT, &tstruct);
    return buf;
}

std::string UtilitySave::calculateTimeDifference(const std::string &logoutTime)
{
    std::string currentTime = getCurrentDateTime();
    std::tm tm_current = {}, tm_logout = {};
    std::istringstream ss_current(currentTime), ss_logout(logoutTime);
    ss_current >> std::get_time(&tm_current, UserData::LOGOUT_TIME_FORMAT);
    ss_logout >> std::get_time(&tm_logout, UserData::LOGOUT_TIME_FORMAT);

    auto tp_current = std::chrono::system_clock::from_time_t(std::mktime(&tm_current));
    auto tp_logout = std::chrono::system_clock::from_time_t(std::mktime(&tm_logout));

    auto duration = std::chrono::duration_cast<std::chrono::minutes>(tp_current - tp_logout);
    int minutes = duration.count();
    int hours = minutes / 60;
    int days = hours / 24;

    if (days > 0)
        return std::to_string(days) + " days";
    else if (hours > 0)
        return std::to_string(hours) + " hours";
    else if (minutes > 0)
        return std::to_string(minutes) + " minutes";
    else
        return "Currently Online";
}
