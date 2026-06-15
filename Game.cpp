#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// ── Save file path ─────────────────────────────────────────────────────────
const char* Game::SAVE_FILE = "barnboss_save.txt";

// ── Constructor ────────────────────────────────────────────────────────────
Game::Game()
	: currentUser(nullptr),
	running(false),
	market(Market::getInstance()),
	taskBoard(TaskBoard::getInstance()),
	scoreboard(ScoreBoard::getInstance())
{
	// Seed the two default tasks from the spec
	taskBoard.addTask(Product(ProductType::Wheat, 0, 0, ProductType::Undefined, 0), 5, 50.0, 10);
	taskBoard.addTask(Product(ProductType::Milk, 0, 0, ProductType::Undefined, 0), 3, 120.0, 20);
}

// ── Entry point ────────────────────────────────────────────────────────────
void Game::run()
{
	load(); // attempt to restore saved state
	running = true;
	printHeader();
	std::cout << GREEN << "> ";
	std::cout.flush();

	std::string line;
	while (running && std::getline(std::cin, line))
	{
		if (line.empty()) continue;
		processCommand(line);
		if(running) std::cout << GREEN << "> ";
	}
}

// ── Header ─────────────────────────────────────────────────────────────────
void Game::printHeader() const
{
	std::cout << BOLDRED << "========================================\n";
	std::cout << "            BARN BOSS\n";
	std::cout << "========================================\n" << RESET;
	std::cout << "Type 'help' for a list of commands." << std::endl;
}

// ── Tokeniser helper ───────────────────────────────────────────────────────
static std::vector<std::string> tokenise(const std::string& line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string tok;
	while (iss >> tok) tokens.push_back(tok);
	return tokens;
}

// ── Command dispatcher ─────────────────────────────────────────────────────
void Game::processCommand(const std::string& line)
{
	std::cout << RESET;
	auto args = tokenise(line);
	if (args.empty()) return;

	const std::string& cmd = args[0];
	std::unique_ptr<Command> cmdPtr = nullptr;

	// ── No user logged in ──────────────────────────────────────────────────
	if (!currentUser)
	{
		try {
			if (cmd == "help") {
				showHelpNotLoggedIn();
				return;
			}
			else if (cmd == "register") {
				cmdPtr = std::make_unique<RegisterCommand>(*this, args);
			}
			else if (cmd == "login") {

				cmdPtr = std::make_unique<LoginCommand>(*this, args);
			}
			else if (cmd == "exit")
			{
				exit();
				return;
			}
			if (cmdPtr)
				cmdPtr->execute();
			else
				std::cout << "Unknown command. Please login or register first.\n";
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
		return;
	}

	// ── Commands available to every logged-in user ─────────────────────────
	try {
		if (cmd == "help") {
			if (currentPlayer())
				showHelpPlayer();
			else if (currentTaskManager())
				showHelpTaskManager();
			else if (currentMarketManager())
				showHelpMarketManager();
			return;
		}
		else if (cmd == "logout")
		{
			cmdPtr = std::make_unique<LogOutCommand>(*this);
		}
		else if (cmd == "profileInfo") {
			cmdPtr = std::make_unique<ProfileInfoCommand>(currentUser);
		}
		else if (cmd == "changePassword") {
			cmdPtr = std::make_unique<ChangePasswordCommand>(currentUser, args);
		}
		else if (cmd == "exit")
		{
			exit();
			return;
		}
		if (cmdPtr) {
			cmdPtr->execute();
			return;
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}


	// ── Player commands ────────────────────────────────────────────────────
	if (currentPlayer())
	{
		try {
			if (cmd == "checkBalance") {
				cmdPtr = std::make_unique<CheckBalanceCommand>(currentPlayer());
			}
			else if (cmd == "checkScore") {
				cmdPtr = std::make_unique<CheckScoreCommand>(currentPlayer());
			}
			else if (cmd == "checkBarn") {
				cmdPtr = std::make_unique<CheckBarnCommand>(currentPlayer());
			}
			else if (cmd == "checkFarm") {
				cmdPtr = std::make_unique<CheckFarmCommand>(currentPlayer());
			}
			else if (cmd == "expandCropland") {
				cmdPtr = std::make_unique<ExpandCroplandCommand>(currentPlayer());
			}
			else if (cmd == "expandFarmland") {
				cmdPtr = std::make_unique<ExpandFarmlandCommand>(currentPlayer());
			}
			else if (cmd == "sowPlant") {
				cmdPtr = std::make_unique<SowPlantCommand>(currentPlayer(), args);
			}
			else if (cmd == "addAnimal") {
				cmdPtr = std::make_unique<AddAnimalCommand>(currentPlayer(), args);
			}
			else if (cmd == "harvest") {
				cmdPtr = std::make_unique<HarvestCommand>(currentPlayer());
			}
			else if (cmd == "openMarketCatalog") {
				cmdPtr = std::make_unique<OpenMarketCommand>(market);
			}
			else if (cmd == "buyItem") {
				cmdPtr = std::make_unique<BuyItemCommand>(currentPlayer(), market, args);
			}
			else if (cmd == "sellItem") {
				cmdPtr = std::make_unique<SellItemCommand>(currentPlayer(), market, args);
			}
			else if (cmd == "showTaskBoard") {
				cmdPtr = std::make_unique<ShowTaskBoardCommand>(taskBoard);
			}
			else if (cmd == "completeTask") {
				cmdPtr = std::make_unique<CompleteTaskCommand>(currentPlayer(), taskBoard, args);
			}
			else if (cmd == "showScoreboard") {
				cmdPtr = std::make_unique<ShowScoreboardCommand>(scoreboard, allPlayers());

			}
			if (cmdPtr)
			{
				cmdPtr->execute();
			}
			else {
				std::cout << "Unknown command." << std::endl;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
		return;
	}

	// ── TaskManager commands ───────────────────────────────────────────────
	if (currentTaskManager())
	{
		try {
			if (cmd == "showTasks")
			{
				cmdPtr = std::make_unique<ShowTaskBoardCommand>(taskBoard);
			}
			else if (cmd == "addTask") {
				cmdPtr = std::make_unique<AddTaskCommand>(*currentTaskManager(), args);
			}
			else if (cmd == "removeTask") {
				cmdPtr = std::make_unique<RemoveTaskCommand>(*currentTaskManager(), args);
			}
			if (cmdPtr) {
				cmdPtr->execute();
			}
			else {

				std::cout << "Unknown command." << std::endl;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
			return;
		}
	}

	// ── MarketManager commands ─────────────────────────────────────────────
	if (currentMarketManager())
	{
		try {
			if (cmd == "openMarketCatalog") {
				cmdPtr = std::make_unique<OpenMarketCommand>(market);
			}
			else if (cmd == "restock") {
				cmdPtr = std::make_unique<RestockCommand>(*currentMarketManager(), args);
			}
			else if (cmd == "changePrice") {
				cmdPtr = std::make_unique<ChangePriceCommand>(*currentMarketManager(), args);
			}
			if (cmdPtr) {
				cmdPtr->execute();
			}
			else {
				std::cout << "Unknown command." << std::endl;
			}
			return;
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void Game::exit()
{
	save();
	std::cout << "Game saved successfully.\nGoodbye!" << std::endl;
	running = false;
}

// ═══════════════════════════════════════════════════════════════════════════
//  AUTH COMMANDS
// ═══════════════════════════════════════════════════════════════════════════
void Game::registerUser(const std::string& username, const std::string& password, const std::string& type)
{
	for (const auto& p : players)
	{
		if (p->getUsername() == username)
		{
			std::cout << "Username already taken.\n";
			return;
		}
	}

	if (MarketManager::isRegistered() &&
		MarketManager::getInstance().getUsername() == username)
	{
		std::cout << "Username already taken.\n";
		return;
	}

	if (TaskManager::isRegistered() &&
		TaskManager::getInstance().getUsername() == username)
	{
		std::cout << "Username already taken.\n";
		return;
	}
	if (type == "Player")
	{
		players.push_back(std::make_unique<Player>(username, password));
	}
	else if (type == "MarketManager")
	{
		if (MarketManager::isRegistered())
		{
			std::cout << "A MarketManager already exists.\n";
			return;
		}

		MarketManager::getInstance().setCredentials(username, password);
	}
	else if (type == "TaskManager")
	{
		if (TaskManager::isRegistered())
		{
			std::cout << "A TaskManager already exists.\n";
			return;
		}

		TaskManager::getInstance().setCredentials(username, password);
	}
	else
	{
		std::cout << "Unknown user type.\n";
		return;
	}

	std::cout << "User registered successfully!\n";
}

void Game::loginUser(const std::string& username, const std::string& password)
{
	for (const auto& p : players)
	{
		if (p->getUsername() == username)
		{
			// validate password via changePassword dry-run approach –
			// instead, expose a check method or compare directly.
			// We access password through a helper on User base.
			// Since password is protected, we add a validate helper on User.
			if (!p->validatePassword(password))
			{
				std::cout << "Incorrect password." << std::endl;
				return;
			}
			currentUser = p.get();
			clearConsole();
			printHeader();
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}
	// Check MarketManager
	if (MarketManager::isRegistered())
	{
		auto& mm = MarketManager::getInstance();
		if (mm.getUsername() == username)
		{
			if (!mm.validatePassword(password))
			{
				std::cout << "Incorrect password." << std::endl;
				return;
			}
			currentUser = &mm;
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}
	// Check TaskManager
	if (TaskManager::isRegistered())
	{
		auto& tm = TaskManager::getInstance();
		if (tm.getUsername() == username)
		{
			if (!tm.validatePassword(password))
			{
				std::cout << "Incorrect password." << std::endl;
				return;
			}
			currentUser = &tm;
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}

	std::cout << "User not found." << std::endl;
}

// ═══════════════════════════════════════════════════════════════════════════
//  SHARED COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::logout()
{
	clearConsole();
	std::cout << "Goodbye, " << currentUser->getUsername() << "!" << std::endl;
	currentUser = nullptr;
	printHeader();
}

void Game::cmdChangePassword(const std::vector<std::string>& args)
{
	if (args.size() != 3)
	{
		std::cout << "Usage: changePassword <oldPassword> <newPassword>" << std::endl;
		return;
	}
	if (args[2].size() < 3)
	{
		std::cout << "New password must be at least 3 characters." << std::endl;
		return;
	}
	if (currentUser->changePassword(args[1], args[2]))
		std::cout << "Password changed successfully." << std::endl;
	else
		std::cout << "Incorrect old password." << std::endl;
}
// ═══════════════════════════════════════════════════════════════════════════
//  UTILITY
// ═══════════════════════════════════════════════════════════════════════════

Player* Game::currentPlayer() const
{
	return dynamic_cast<Player*>(currentUser);
}

TaskManager* Game::currentTaskManager() const
{
	return dynamic_cast<TaskManager*>(currentUser);
}

MarketManager* Game::currentMarketManager() const
{
	return dynamic_cast<MarketManager*>(currentUser);
}

std::vector<Player*> Game::allPlayers() const
{
	std::vector<Player*> result;
	for (const auto& p : players)
		result.push_back(p.get());
	return result;
}

// ═══════════════════════════════════════════════════════════════════════════
//  SAVE / LOAD
// ═══════════════════════════════════════════════════════════════════════════

void Game::save()
{
	std::ofstream out(SAVE_FILE);
	if (!out)
	{
		std::cout << "Warning: could not open save file." << std::endl;
		return;
	}

	// Players
	out << players.size() << "\n";
	for (const auto& p : players)
		p->saveToFile(out);

	// MarketManager
	out << (MarketManager::isRegistered() ? 1 : 0) << "\n";
	if (MarketManager::isRegistered())
	{
		auto& mm = MarketManager::getInstance();
		out << mm.getUsername() << " " << mm.getPasswordRaw() << "\n";
	}

	// TaskManager
	out << (TaskManager::isRegistered() ? 1 : 0) << "\n";
	if (TaskManager::isRegistered())
	{
		auto& tm = TaskManager::getInstance();
		out << tm.getUsername() << " " << tm.getPasswordRaw() << "\n";
	}

	// Market state
	market.saveToFile(out);

	// TaskBoard state
	taskBoard.saveToFile(out);
}

void Game::load()
{
	std::ifstream in(SAVE_FILE);
	if (!in)
	{
		// No save file – start fresh with default task board already seeded
		// in the constructor.
		return;
	}

	// Clear default tasks (they were seeded in constructor; save file has them)
	// We reload the full task board from file instead.
	// Players
	players.clear();
	size_t playerCount;
	in >> playerCount;
	in.ignore();

	for (size_t i = 0; i < playerCount; i++)
	{
		std::string type, uname, pwd;
		in >> type >> uname >> pwd;
		auto player = std::make_unique<Player>(uname, pwd);
		player->loadFromFile(in);
		players.push_back(std::move(player));
	}

	// MarketManager
	int mmFlag;
	in >> mmFlag;
	if (mmFlag)
	{
		std::string uname, pwd;
		in >> uname >> pwd;
		MarketManager::getInstance().setCredentials(uname, pwd);
	}

	// TaskManager
	int tmFlag;
	in >> tmFlag;
	if (tmFlag)
	{
		std::string uname, pwd;
		in >> uname >> pwd;
		TaskManager::getInstance().setCredentials(uname, pwd);
	}

	// Market state
	market.loadFromFile(in);

	// TaskBoard state (replaces the default tasks)
	// First clear the default tasks we inserted in the constructor
	// by re-initialising via loadFromFile
	taskBoard.loadFromFile(in);

	std::cout << "Game loaded successfully." << std::endl;
}
void Game::showHelpNotLoggedIn() const
{
	std::cout << "Available commands:\n"
		<< CYAN << "help\n" << RESET
		<< "register <username> <password> <type>\n"
		<< "login <username> <password>\n"
		<< BOLDRED << "exit\n" << RESET;
}

void Game::showHelpPlayer() const
{
	std::cout << "Available commands:\n"
		<< CYAN << "help\n" << RESET
		<< "logout\n"
		<< "profileInfo\n"
		<< "changePassword <oldPassword> <newPassword>\n"
		<< "checkBalance\n"
		<< "checkScore\n"
		<< "checkBarn\n"
		<< "checkFarm\n"
		<< "expandCropland\n"
		<< "expandFarmland\n"
		<< "sowPlant <seedName>\n"
		<< "addAnimal <animalName>\n"
		<< "harvest\n"
		<< "openMarketCatalog\n"
		<< "buyItem <productName> <quantity>\n"
		<< "sellItem <productName> <quantity>\n"
		<< "showTaskBoard\n"
		<< "completeTask <taskId>\n"
		<< "showScoreboard\n";
}

void Game::showHelpTaskManager() const
{
	std::cout << "Available commands:\n"
		<< CYAN << "help\n" << RESET
		<< "logout\n"
		<< "profileInfo\n"
		<< "changePassword <oldPassword> <newPassword>\n"
		<< "showTasks\n"
		<< "addTask <product> <quantity> <rewardBalance> <rewardScore>\n"
		<< "removeTask <taskId>\n";
}

void Game::showHelpMarketManager() const
{
	std::cout << "Available commands:\n"
		<< CYAN << "help\n" << RESET
		<< "logout\n"
		<< "profileInfo\n"
		<< "changePassword <oldPassword> <newPassword>\n"
		<< "openMarketCatalog\n"
		<< "restock <productName> <quantity>\n"
		<< "changePrice <productName> <newPrice>\n";
}