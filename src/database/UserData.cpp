#include <UserData.hpp>

const char *UserData::gameModeNames[GameMode::GameModeCount] = {"eng_eng_quiz", "eng_vie_quiz", "vie_eng_quiz", "eng_emo_quiz"};

UserData::UserData()
    : username(""), password("")
{
    for (int i = 0; i < GameMode::GameModeCount; ++i)
    {
        highscore.at(i) = 0;
    }
}

UserData::UserData(std::string username, std::string password, int eng_eng_quiz, int eng_vie_quiz, int vie_eng_quiz, int eng_emo_quiz)
    : username(username), password(password)
{
    highscore.at(GameMode::eng_eng_quiz) = eng_eng_quiz;
    highscore.at(GameMode::eng_vie_quiz) = eng_vie_quiz;
    highscore.at(GameMode::vie_eng_quiz) = vie_eng_quiz;
    highscore.at(GameMode::eng_emo_quiz) = eng_emo_quiz;
}

UserData::UserData(std::string username, std::string password)
    : username(username), password(password)
{
    for (int i = 0; i < GameMode::GameModeCount; ++i)
        highscore.at(i) = 0;
}

UserData::UserData(const UserData &other)
    : username(other.getUsername()), password(other.getPassword()), highscore(other.getHighscore())
{
}

std::string UserData::getUsername() const
{
    return username;
}

std::string UserData::getPassword() const
{
    return password;
}

std::array<int, UserData::GameMode::GameModeCount> UserData::getHighscore() const
{
    return highscore;
}

int UserData::getHighscore(GameMode mode) const
{
    return highscore.at(mode);
}

void UserData::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

void UserData::setHighscore(int newHighscore, GameMode gameMode)
{
    highscore.at(gameMode) = newHighscore;
}

void UserData::updateHighscore(int newHighscore, GameMode gameMode)
{
    if (newHighscore > highscore.at(gameMode))
    {
        highscore.at(gameMode) = newHighscore;
    }
}

bool UserData::notAUser() const
{
    return (username == "") || (password == "");
}
