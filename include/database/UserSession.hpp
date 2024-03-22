#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <UserRepo.hpp>
#include <UserData.hpp>
#include <UtilitySave.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>

class UserSession
{
public:
    typedef std::pair<std::string, std::string> UserAccess;
    typedef std::vector<UserAccess> UserAccesses;

public:
    static UserSession &getInstance();
    UserSession &operator=(const UserSession &) = delete;
    UserSession(const UserSession &) = delete;

    ~UserSession();

    UserData &getCurrentUser();
    const UserData &getCurrentUser() const;

    bool isLoggedin() const;

    void loginUser(const std::string &username, const std::string &password);
    void logoutUser();

    UserSession::UserAccesses loadLoginState(const std::string &filename);
    void saveLoginState(const std::string &filename);

private:
    UserSession();
    UserData currentUser;
    UserRepo &repo;
    bool isLogin;

    static const char *loginStateFilename;
};

#endif