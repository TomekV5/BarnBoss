#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include "User.h"
#include "TaskBoard.h"
#include "ScoreBoard.h"
#include "Market.h"

class Game
{
private:
	std::vector<std::unique_ptr<User>> users;

	User* currentUser;
	MarketManager marketManager;
	Market* market;
	TaskBoard* taskBoard;
	ScoreBoard* scoreboard;

	bool running;
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

public:
	Game();
	~Game();

	void LoadFromFile(const std::string& filename);
	void CreateNewGame();
	void run();

private:
	
};