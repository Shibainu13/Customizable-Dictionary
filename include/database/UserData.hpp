#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <string>
#include <array>

class UserData
{
public:
    enum GameMode
    {
        eng_eng_quiz,
        eng_vie_quiz,
        vie_eng_quiz,
        eng_emo_quiz,
        GameModeCount
    };
    static const char *gameModeNames[GameMode::GameModeCount];

public:
    UserData();
    UserData(std::string username, std::string password, int eng_eng_quiz, int eng_vie_quiz, int vie_eng_quiz, int eng_emo_quiz);
    UserData(std::string username, std::string password);
    UserData(const UserData &other);

    std::string getUsername() const;
    std::string getPassword() const;
    std::array<int, GameMode::GameModeCount> getHighscore() const;
    int getHighscore(GameMode mode) const;

    void setPassword(const std::string &newPassword);
    void setHighscore(int newHighscore, GameMode gameMode);
    void updateHighscore(int newHighscore, GameMode gameMode);
    bool notAUser() const;

private:
    std::string username;
    std::string password;
    std::array<int, GameMode::GameModeCount> highscore;
};

#endif