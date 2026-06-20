#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

Game::Game()
	: currentUser(nullptr), currentPlayer(nullptr), currentMarketManager(nullptr), currentTaskManager(nullptr),
	running(false), megarun(false),
	market(Market::getInstance()),
	taskBoard(TaskBoard::getInstance()),
	scoreboard(ScoreBoard::getInstance())
{
	taskBoard.addTask(Product(ProductType::Wheat, 0, 0, ProductType::Undefined, 0), 5, 50.0, 10);
	taskBoard.addTask(Product(ProductType::Milk, 0, 0, ProductType::Undefined, 0), 3, 120.0, 20);
}

void Game::run()
{
	megarun = true;
	while (megarun) {
		clearConsole();
		load();
		running = true;
		printHeader();
		std::cout << "Type 'help' for a list of commands." << std::endl;
		std::cout << GREEN << "> ";
		std::cout.flush();

		std::string line;
		while (running && std::getline(std::cin, line))
		{
			if (line.empty()) continue;
			processCommand(line);
			if (running) std::cout << GREEN << "> ";
		}
	}
}

void Game::printHeader() const
{
	std::cout << BOLDRED << "========================================\n";
	std::cout << "            BARN BOSS\n";
	std::cout << "========================================\n" << RESET;
}

static std::vector<std::string> tokenise(const std::string& line)
{
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string tok;
	while (iss >> tok) tokens.push_back(tok);
	return tokens;
}

void Game::processCommand(const std::string& line)
{
	std::cout << RESET;
	auto args = tokenise(line);
	if (args.empty()) return;

	const std::string& cmd = args[0];
	std::unique_ptr<Command> cmdPtr = nullptr;

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
			else if (cmd == "exitFile") {
				exitFile();
				return;
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

	try {
		if (cmd == "help") {
			if (currentPlayer)
				showHelpPlayer();
			else if (currentTaskManager)
				showHelpTaskManager();
			else if (currentMarketManager)
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
		else if (cmd == "exitFile") {
			exitFile();
			return;
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

	if (currentPlayer)
	{
		try {
			if (cmd == "checkBalance") {
				cmdPtr = std::make_unique<CheckBalanceCommand>(currentPlayer);
			}
			else if (cmd == "checkScore") {
				cmdPtr = std::make_unique<CheckScoreCommand>(currentPlayer);
			}
			else if (cmd == "checkBarn") {
				cmdPtr = std::make_unique<CheckBarnCommand>(currentPlayer);
			}
			else if (cmd == "checkFarm") {
				cmdPtr = std::make_unique<CheckFarmCommand>(currentPlayer);
			}
			else if (cmd == "expandCropland") {
				cmdPtr = std::make_unique<ExpandCroplandCommand>(currentPlayer);
			}
			else if (cmd == "expandFarmland") {
				cmdPtr = std::make_unique<ExpandFarmlandCommand>(currentPlayer);
			}
			else if (cmd == "sowPlant") {
				cmdPtr = std::make_unique<SowPlantCommand>(currentPlayer, args);
			}
			else if (cmd == "addAnimal") {
				cmdPtr = std::make_unique<AddAnimalCommand>(currentPlayer, args);
			}
			else if (cmd == "harvest") {
				cmdPtr = std::make_unique<HarvestCommand>(currentPlayer);
			}
			else if (cmd == "openMarketCatalog") {
				cmdPtr = std::make_unique<OpenMarketCommand>(market);
			}
			else if (cmd == "buyItem") {
				cmdPtr = std::make_unique<BuyItemCommand>(currentPlayer, market, args);
			}
			else if (cmd == "sellItem") {
				cmdPtr = std::make_unique<SellItemCommand>(currentPlayer, market, args);
			}
			else if (cmd == "showTaskBoard") {
				cmdPtr = std::make_unique<ShowTaskBoardCommand>(taskBoard);
			}
			else if (cmd == "completeTask") {
				cmdPtr = std::make_unique<CompleteTaskCommand>(currentPlayer, taskBoard, args);
			}
			else if (cmd == "showScoreboard") {
				cmdPtr = std::make_unique<ShowScoreboardCommand>(scoreboard, allPlayers());
			}
			else if (cmd == "advanceCycle") {
				cmdPtr = std::make_unique<AdvanceCycleCommand>(currentPlayer);
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

	if (currentTaskManager)
	{
		try {
			if (cmd == "showTasks")
			{
				cmdPtr = std::make_unique<ShowTaskBoardCommand>(taskBoard);
			}
			else if (cmd == "addTask") {
				cmdPtr = std::make_unique<AddTaskCommand>(*currentTaskManager, args);
			}
			else if (cmd == "removeTask") {
				cmdPtr = std::make_unique<RemoveTaskCommand>(*currentTaskManager, args);
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

	if (currentMarketManager)
	{
		try {
			if (cmd == "openMarketCatalog") {
				cmdPtr = std::make_unique<OpenMarketCommand>(market);
			}
			else if (cmd == "restock") {
				cmdPtr = std::make_unique<RestockCommand>(*currentMarketManager, args);
			}
			else if (cmd == "changePrice") {
				cmdPtr = std::make_unique<ChangePriceCommand>(*currentMarketManager, args);
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
	megarun = false;
	running = false;
}

void Game::exitFile()
{
	save();
	running = false;
}

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
			if (!p->validatePassword(password))
			{
				std::cout << "Incorrect password." << std::endl;
				return;
			}
			currentUser = p.get();
			currentPlayer = p.get();
			clearConsole();
			printHeader();
			std::cout << "Type 'help' for a list of commands." << std::endl;
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}
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
			currentMarketManager = &mm;
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}
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
			currentTaskManager = &tm;
			std::cout << "Welcome, " << username << "!" << std::endl;
			return;
		}
	}

	std::cout << "User not found." << std::endl;
}

void Game::logout()
{
	clearConsole();
	std::cout << "Goodbye, " << currentUser->getUsername() << "!" << std::endl;
	currentUser = nullptr;
	currentPlayer = nullptr;
	currentMarketManager = nullptr;
	currentTaskManager = nullptr;
	save();
	printHeader();
	std::cout << "Type 'help' for a list of commands." << std::endl;
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

std::vector<Player*> Game::allPlayers() const
{
	std::vector<Player*> result;
	for (const auto& p : players)
		result.push_back(p.get());
	return result;
}


namespace fs = std::filesystem;

std::vector<std::string> Game::getSaveFiles() const
{
	std::vector<std::string> saves;

	if (!fs::exists("saves"))
	{
		fs::create_directory("saves");
		return saves;
	}

	for (const auto& entry : fs::directory_iterator("saves"))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".txt")
		{
			saves.push_back(entry.path().string());
		}
	}

	return saves;
}
void Game::selectSaveFile()
{
	std::vector<std::string> saves = getSaveFiles();

	printHeader();

	std::cout << "Existing saves:\n";

	for (size_t i = 0; i < saves.size(); i++)
	{
		std::filesystem::path p(saves[i]);

		std::cout
			<< i + 1
			<< ". "
			<< p.filename().string()
			<< '\n';
	}

	std::cout << "\n0. Create new save\n";

	std::cout << "\nChoice: ";
	int choice = safeReadInt(0, saves.size());

	if (choice == 0)
	{
		std::string name;

		std::cout << "Enter save name: ";
		std::getline(std::cin, name);

		if (name.find(".txt") == std::string::npos)
		{
			name += ".txt";
		}

		currentSaveFile = "saves/" + name;
		clearConsole();
		std::cout << "New game created.\n";
	}
	else if (choice > 0 &&
		choice <= static_cast<int>(saves.size()))
	{
		currentSaveFile = saves[choice - 1];

		loadFromFile(currentSaveFile);
		clearConsole();
		std::cout << "Loaded "
			<< currentSaveFile
			<< '\n';
	}
	else
	{
		std::cout << "Invalid choice.\n";
		selectSaveFile();
	}
}
void Game::loadFromFile(std::string filename)
{
	std::ifstream in(filename);
	players.clear();
	size_t playerCount;
	in >> playerCount;
	in.ignore();

	for (size_t i = 0; i < playerCount; i++)
	{
		std::string type, username, password;
		in >> type >> username >> password;
		auto player = std::make_unique<Player>(username, password);
		player->loadFromFile(in);
		players.push_back(std::move(player));
	}

	int marketManagerFlag;
	in >> marketManagerFlag;
	if (marketManagerFlag)
	{
		std::string username, password;
		in >> username >> password;
		MarketManager::getInstance().setCredentials(username, password);
	}

	int taskManagerFlag;
	in >> taskManagerFlag;
	if (taskManagerFlag)
	{
		std::string username, password;
		in >> username >> password;
		TaskManager::getInstance().setCredentials(username, password);
	}

	market.loadFromFile(in);

	taskBoard.loadFromFile(in);

}
void Game::save()
{
	std::ofstream out(currentSaveFile);
	if (!out)
	{
		std::cout << "Warning: could not open save file." << std::endl;
		return;
	}

	out << players.size() << "\n";
	for (const auto& p : players)
		p->saveToFile(out);

	out << (MarketManager::isRegistered() ? 1 : 0) << "\n";
	if (MarketManager::isRegistered())
	{
		auto& marketManager = MarketManager::getInstance();
		out << marketManager.getUsername() << " " << marketManager.getPasswordRaw() << "\n";
	}

	out << (TaskManager::isRegistered() ? 1 : 0) << "\n";
	if (TaskManager::isRegistered())
	{
		auto& taskManager = TaskManager::getInstance();
		out << taskManager.getUsername() << " " << taskManager.getPasswordRaw() << "\n";
	}

	market.saveToFile(out);

	taskBoard.saveToFile(out);
}

void Game::load()
{
	currentUser = nullptr;
	currentPlayer = nullptr;
	currentMarketManager = nullptr;
	currentTaskManager = nullptr;
	MarketManager::getInstance().reset();
	TaskManager::getInstance().reset();
	players.clear();
	market.reset();
	selectSaveFile();
}
void Game::showHelpNotLoggedIn() const
{
	std::cout << "Available commands:\n"
		<< CYAN << "help\n" << RESET
		<< "register <username> <password> <type>\n"
		<< "login <username> <password>\n"
		<< RED << "exitFile\n"
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
		<< "showScoreboard\n"
		<< "advanceCycle\n";
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