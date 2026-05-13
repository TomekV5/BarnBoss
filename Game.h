#pragma once

#include <vector>
#include <string>
#include "User.h"
#include "TaskBoard.h"
#include "ScoreBoard.h"
#include "Market.h"

class Game
{
private:
    std::vector<User*> users;

    User* currentUser;

    Market market;
    TaskBoard taskBoard;
    ScoreBoard scoreboard;

    bool running;

public:
    Game();
    ~Game();

    void run();

private:
    void processCommand(const std::string& command);

    // authentication
    void registerUser(const std::vector<std::string>& args);
    void loginUser(const std::vector<std::string>& args);
    void logoutUser();

    // helper methods
    User* findUserByUsername(const std::string& username);

    // save/load
    void save();
    void load();
};