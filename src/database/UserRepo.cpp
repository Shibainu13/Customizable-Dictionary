#include <UserRepo.hpp>

UserRepo::UserRepo()
    : db("userdata/users.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    // db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, highscore INTEGER);");
    db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, logout_time TEXT);");
    db.exec("CREATE TABLE IF NOT EXISTS highscores (username TEXT PRIMARY KEY, eng_eng_quiz INTEGER, eng_vie_quiz INTEGER, vie_eng_quiz INTEGER, eng_emo_quiz INTEGER);");
}

UserRepo &UserRepo::getInstance()
{
    static UserRepo instance;
    return instance;
}

SQLite::Database &UserRepo::getDatabase()
{
    return db;
}

UserData UserRepo::getUserByLogin(const std::string &username, const std::string &password) const
{
    SQLite::Statement userQuery(db, "SELECT * FROM users WHERE username = ? AND password = ?;");
    userQuery.bind(1, username);
    userQuery.bind(2, password);

    SQLite::Statement scoreQuery(db, "SELECT * FROM highscores WHERE username = ?;");
    scoreQuery.bind(1, username);

    if (userQuery.executeStep() && scoreQuery.executeStep())
        return UserData(userQuery.getColumn(0), userQuery.getColumn(1), userQuery.getColumn(2), scoreQuery.getColumn(1), scoreQuery.getColumn(2), scoreQuery.getColumn(3), scoreQuery.getColumn(4));

    return UserData("", "");
}

bool UserRepo::checkUser(const std::string &username, const std::string &password) const
{
    UserData user = getUserByLogin(username, password);
    return !user.notAUser();
}

UserRepo::Leaderboard UserRepo::getLeaderboard(UserData::GameMode gameMode) const
{
    std::string GameModeQuery;
    switch (gameMode)
    {
    case UserData::GameMode::eng_eng_quiz:
        GameModeQuery = "eng_eng_quiz";
        break;
    case UserData::GameMode::eng_vie_quiz:
        GameModeQuery = "eng_vie_quiz";
        break;
    case UserData::GameMode::vie_eng_quiz:
        GameModeQuery = "vie_eng_quiz";
        break;
    case UserData::GameMode::eng_emo_quiz:
        GameModeQuery = "eng_emo_quiz";
        break;
    default:
        throw std::runtime_error("REPO ERR: Unknown Game mode.\n");
    }

    UserRepo::Leaderboard leaderboard;
    SQLite::Statement scoreQuery(db, "SELECT * FROM highscores ORDER BY " + GameModeQuery + " DESC LIMIT 20;");
    while (scoreQuery.executeStep())
    {
        std::pair<std::string, int> userScore(scoreQuery.getColumn(0), scoreQuery.getColumn(static_cast<int>(gameMode) + 1));
        leaderboard.emplace_back(userScore);
    }
    return leaderboard;
}

bool UserRepo::addUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("REPO ERR: Updating not a user");
    
    if (userExist(user.getUsername()))
    {
        std::cerr << "REPO LOG: User already exists.\n";
        return false;
    }

    SQLite::Statement userQuery(db, "INSERT INTO users (username, password, logout_time) VALUES (?, ?, ?);");
    userQuery.bind(1, user.getUsername());
    userQuery.bind(2, user.getPassword());
    userQuery.bind(3, user.getLastLogOutTime());

    SQLite::Statement scoreQuery(db, "INSERT INTO highscores (username, eng_eng_quiz, eng_vie_quiz, vie_eng_quiz, eng_emo_quiz) VALUES (?, ?, ?, ?, ?);");
    scoreQuery.bind(1, user.getUsername());
    scoreQuery.bind(2, user.getHighscore(UserData::GameMode::eng_eng_quiz));
    scoreQuery.bind(3, user.getHighscore(UserData::GameMode::eng_vie_quiz));
    scoreQuery.bind(4, user.getHighscore(UserData::GameMode::vie_eng_quiz));
    scoreQuery.bind(5, user.getHighscore(UserData::GameMode::eng_emo_quiz));

    userQuery.exec();
    scoreQuery.exec();
    return true;
}

void UserRepo::updateUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("REPO ERR: Updating not a user");

    if (!userExist(user.getUsername()))
        throw std::runtime_error("User with username " + user.getUsername() + " not found.");

    SQLite::Statement userQuery(db, "UPDATE users SET password = ?, logout_time = ? WHERE username = ?;");
    userQuery.bind(1, user.getPassword());
    userQuery.bind(3, user.getUsername());
    userQuery.bind(2, user.getLastLogOutTime());

    SQLite::Statement scoreQuery(db, "UPDATE highscores SET eng_eng_quiz = ?, eng_vie_quiz = ?, vie_eng_quiz = ?, eng_emo_quiz = ? WHERE username = ?;");
    scoreQuery.bind(1, user.getHighscore(UserData::GameMode::eng_eng_quiz));
    scoreQuery.bind(2, user.getHighscore(UserData::GameMode::eng_vie_quiz));
    scoreQuery.bind(3, user.getHighscore(UserData::GameMode::vie_eng_quiz));
    scoreQuery.bind(4, user.getHighscore(UserData::GameMode::eng_emo_quiz));
    scoreQuery.bind(5, user.getUsername());

    userQuery.exec();
    scoreQuery.exec();
}

void UserRepo::deleteUser(const std::string &username)
{
    if (!userExist(username))
        throw std::runtime_error("REPO ERR: User with username " + username + " not found.");

    SQLite::Statement userQuery(db, "DELETE FROM users WHERE username = ?;");
    userQuery.bind(1, username);

    SQLite::Statement scoreQuery(db, "DELETE FROM highscores WHERE username = ?;");
    scoreQuery.bind(1, username);

    userQuery.exec();
    scoreQuery.exec();
}

bool UserRepo::userExist(const std::string &username)
{
    SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM users WHERE username = ? LIMIT 1);");
    query.bind(1, username);

    if (query.executeStep())
        return query.getColumn(0).getInt() > 0;

    return false;
}

void UserRepo::updatePassword(const std::string &username, const std::string &newPassword)
{
    if (username == "" || newPassword == "")
        throw std::runtime_error("REPO ERR: Updating not a user");

    if (!userExist(username))
        throw std::runtime_error("User with username " + username + " not found.");

    SQLite::Statement userQuery(db, "UPDATE users SET password = ? WHERE username = ?;");
    userQuery.bind(1, newPassword);
    userQuery.bind(2, username);

    userQuery.exec();
}
