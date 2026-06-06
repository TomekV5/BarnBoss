#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include "TaskBoard.h"
#include "ScoreBoard.h"
#include "Market.h"

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

    // Unauthenticated commands
    void cmdRegister(const std::vector<std::string>& args);
    void cmdLogin(const std::vector<std::string>& args);

    // Commands available to all logged-in users
    void cmdLogout();
    void cmdProfileInfo();
    void cmdChangePassword(const std::vector<std::string>& args);

    // Player commands
    void cmdCheckBalance();
    void cmdCheckScore();
    void cmdCheckBarn();
    void cmdCheckFarm();
    void cmdExpandCropland();
    void cmdExpandFarmland();
    void cmdSowPlant(const std::vector<std::string>& args);
    void cmdAddAnimal(const std::vector<std::string>& args);
    void cmdHarvest();
    void cmdOpenMarket();
    void cmdBuyItem(const std::vector<std::string>& args);
    void cmdSellItem(const std::vector<std::string>& args);
    void cmdShowTaskBoard();
    void cmdCompleteTask(const std::vector<std::string>& args);
    void cmdShowScoreboard();

    // TaskManager commands
    void cmdShowTasks();
    void cmdAddTask(const std::vector<std::string>& args);
    void cmdRemoveTask(const std::vector<std::string>& args);

    // MarketManager commands
    void cmdRestock(const std::vector<std::string>& args);
    void cmdChangePrice(const std::vector<std::string>& args);

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
    Game();
    void run();
};