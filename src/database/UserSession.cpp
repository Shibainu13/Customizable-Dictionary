#include <UserSession.hpp>
#include <cassert>

const char *UserSession::loginStateFilename = "userdata/login.txt";

UserSession &UserSession::getInstance()
{
    static UserSession instance;
    return instance;
}

UserSession::UserSession()
    : isLogin(false), repo(UserRepo::getInstance())
{
}

UserSession::~UserSession()
{
    if (isLoggedin())
    {
        repo.updateUser(currentUser);
    }
}

bool UserSession::isLoggedin() const
{
    return isLogin;
}

void UserSession::loginUser(const std::string &username, const std::string &password)
{
    if (isLogin)
    {
        throw std::runtime_error("An account has already logged in. Please log out first\n");
    }

    currentUser = repo.getUserByLogin(username, password);

    if (currentUser.notAUser())
    {
        throw std::runtime_error("incorrect username or password.\n");
    }

    isLogin = true;
    std::cout << username << " logged in.\n";
}

void UserSession::logoutUser()
{
    saveLoginState(loginStateFilename);
    if (!isLoggedin())
    {
        std::cerr << "User is not logged in!\n";
        return;
    }

    assert(!currentUser.notAUser());

    std::cout << currentUser.getUsername() << " logged out.\n";

    isLogin = false;
    currentUser = UserData();

}

UserSession::UserAccesses UserSession::loadLoginState(const std::string &filename)
{
    UserAccesses userList;
    std::ifstream inf{filename};
    if (!inf)
    {
        std::cerr << filename + " not found.\n";
        return userList;
    }


    while (inf)
    {
        std::string name, logoutTime;
        inf >> name >> logoutTime;
        if (name != "" && logoutTime != "")
        {
            std::string duration = UtilitySave::calculateTimeDifference(logoutTime);
            UserAccess user(name, duration);
            userList.push_back(user);
        }
    }
    inf.close();
    return userList;
}

void UserSession::saveLoginState(const std::string &filename)
{
    std::ofstream outf(filename, std::ofstream::out | std::ofstream::app);
    outf << currentUser.getUsername() << ' ' << UtilitySave::getCurrentDateTime() << "\n";
    currentUser.setLogoutTime(UtilitySave::getCurrentDateTime());
    repo.updateUser(currentUser);
    std::cerr << "Login state saved.\n";
    outf.close();
}

UserData &UserSession::getCurrentUser()
{
    return currentUser;
}

const UserData &UserSession::getCurrentUser() const
{
    return currentUser;
}