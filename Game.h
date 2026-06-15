#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Helper.h"
#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include "TaskBoard.h"
#include "ScoreBoard.h"
#include "Market.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "LogOutCommand.h"
#include "ProfileInfoCommand.h"
#include "ChangePasswordCommand.h"
#include "CheckBalanceCommand.h"
#include "CheckScoreCommand.h"
#include "CheckBarnCommand.h"
#include "CheckFarmCommand.h"
#include "ExpandCroplandCommand.h"
#include "ExpandFarmlandCommand.h"
#include "SowPlantCommand.h"
#include "AddAnimalCommand.h"
#include "HarvestCommand.h"
#include "OpenMarketCommand.h"
#include "BuyItemCommand.h"
#include "SellItemCommand.h"
#include "ShowTaskBoardCommand.h"
#include "CompleteTaskCommand.h"
#include "ShowScoreboardCommand.h"
#include "AddTaskCommand.h"
#include "RemoveTaskCommand.h"
#include "RestockCommand.h"
#include "ChangePriceCommand.h"
#include "AdvanceCycleCommand.h"

class Game
{
private:
	
    // ── State ──────────────────────────────────────────────────────────────
    std::vector<std::unique_ptr<Player>> players; // all registered Players
    User* currentUser;
    bool running;

    // Singletons – stored as references so we never delete them
    Market& market;
    TaskBoard& taskBoard;
    ScoreBoard& scoreboard;

    // ── Internal helpers ───────────────────────────────────────────────────
    void printHeader() const;
    void processCommand(const std::string& line);

    void exit();

    
    // Unauthenticated commands
    void registerUser(const std::string& username,
        const std::string& password,
        const std::string& type);
    void loginUser(const std::string& username, const std::string& password);
    void logout();

    // Commands available to all logged-in users
    void cmdChangePassword(const std::vector<std::string>& args);

	//comand helpers
	void showHelpNotLoggedIn() const;
	void showHelpPlayer() const;
	void showHelpTaskManager() const;
	void showHelpMarketManager() const;

    // Save / load
    static const char* SAVE_FILE;
    void save();
    void load();

    // Utility
    Player* currentPlayer() const;  // nullptr if not a Player
    TaskManager* currentTaskManager() const;
    MarketManager* currentMarketManager() const;
    std::vector<Player*> allPlayers() const;

public:
    friend class ProfileInfoCommand;
	friend class LogOutCommand;
	friend class LoginCommand;
	friend class RegisterCommand;
	friend class ChangePasswordCommand;
    Game();
    void run();
   
};