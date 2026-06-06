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

    std::string line;
    if (!currentUser) {
        showHelpNotLoggedIn();
    }
    else if (currentPlayer())
    {
        showHelpPlayer();
    }
    else if (currentTaskManager())
    {
        showHelpTaskManager();
    }
    else if (currentMarketManager())
    {
        showHelpMarketManager();
    }
    while (running && std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::cout << "> ";
        processCommand(line);
        if (!currentUser) {
            showHelpNotLoggedIn();
        }
        else if (currentPlayer())
        {
            showHelpPlayer();
        }
        else if (currentTaskManager())
        {
            showHelpTaskManager();
        }
        else if (currentMarketManager())
        {
            showHelpMarketManager();
        }
    }
}

// ── Header ─────────────────────────────────────────────────────────────────
void Game::printHeader() const
{
    std::cout << "========================================\n";
    std::cout << "            BARN BOSS\n";
    std::cout << "========================================\n";
    std::cout << "> ";
    std::cout.flush();
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
    auto args = tokenise(line);
    if (args.empty()) return;

    const std::string& cmd = args[0];

    // ── No user logged in ──────────────────────────────────────────────────
    if (!currentUser)
    {
        if (cmd == "register") cmdRegister(args);
        else if (cmd == "login")    cmdLogin(args);
        else if (cmd == "exit")
        {
            save();
            std::cout << "Game saved successfully.\nGoodbye!" << std::endl;
            running = false;
        }
        else
            std::cout << "Unknown command. Please login or register first." << std::endl;
        return;
    }

    // ── Commands available to every logged-in user ─────────────────────────
    if (cmd == "logout") { cmdLogout(); return; }
    else if (cmd == "profileInfo") { cmdProfileInfo(); return; }
    else if (cmd == "changePassword") { cmdChangePassword(args); return; }
    else if (cmd == "exit")
    {
        save();
        std::cout << "Game saved successfully.\nGoodbye!" << std::endl;
        running = false;
        return;
    }

    // ── Player commands ────────────────────────────────────────────────────
    if (currentPlayer())
    {
        if (cmd == "checkBalance") cmdCheckBalance();
        else if (cmd == "checkScore") cmdCheckScore();
        else if (cmd == "checkBarn") cmdCheckBarn();
        else if (cmd == "checkFarm") cmdCheckFarm();
        else if (cmd == "expandCropland") cmdExpandCropland();
        else if (cmd == "expandFarmland") cmdExpandFarmland();
        else if (cmd == "sowPlant") cmdSowPlant(args);
        else if (cmd == "addAnimal") cmdAddAnimal(args);
        else if (cmd == "harvest") cmdHarvest();
        else if (cmd == "openMarketCatalog") cmdOpenMarket();
        else if (cmd == "buyItem") cmdBuyItem(args);
        else if (cmd == "sellItem") cmdSellItem(args);
        else if (cmd == "showTaskBoard") cmdShowTaskBoard();
        else if (cmd == "completeTask") cmdCompleteTask(args);
        else if (cmd == "showScoreboard") cmdShowScoreboard();
        else
            std::cout << "Unknown command." << std::endl;
        return;
    }

    // ── TaskManager commands ───────────────────────────────────────────────
    if (currentTaskManager())
    {
        if (cmd == "showTasks")  cmdShowTasks();
        else if (cmd == "addTask")    cmdAddTask(args);
        else if (cmd == "removeTask") cmdRemoveTask(args);
        else
            std::cout << "Unknown command." << std::endl;
        return;
    }

    // ── MarketManager commands ─────────────────────────────────────────────
    if (currentMarketManager())
    {
        if (cmd == "openMarketCatalog") cmdOpenMarket();
        else if (cmd == "restock")           cmdRestock(args);
        else if (cmd == "changePrice")       cmdChangePrice(args);
        else
            std::cout << "Unknown command." << std::endl;
        return;
    }

    std::cout << "Unknown command." << std::endl;
}

// ═══════════════════════════════════════════════════════════════════════════
//  AUTH COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::cmdRegister(const std::vector<std::string>& args)
{
    if (args.size() != 4)
    {
        std::cout << "Usage: register <username> <password> <type>" << std::endl;
        return;
    }
    const std::string& uname = args[1];
    const std::string& pwd = args[2];
    const std::string& type = args[3];

    if (pwd.size() < 3)
    {
        std::cout << "Password must be at least 3 characters." << std::endl;
        return;
    }

    // Check username uniqueness across players and singletons
    for (const auto& p : players)
        if (p->getUsername() == uname)
        {
            std::cout << "Username already taken." << std::endl;
            return;
        }
    if (MarketManager::isRegistered() &&
        MarketManager::getInstance().getUsername() == uname)
    {
        std::cout << "Username already taken." << std::endl;
        return;
    }
    if (TaskManager::isRegistered() &&
        TaskManager::getInstance().getUsername() == uname)
    {
        std::cout << "Username already taken." << std::endl;
        return;
    }

    if (type == "Player")
    {
        players.push_back(std::make_unique<Player>(uname, pwd));
        std::cout << "User registered successfully!" << std::endl;
    }
    else if (type == "MarketManager")
    {
        if (MarketManager::isRegistered())
        {
            std::cout << "A MarketManager already exists." << std::endl;
            return;
        }
        MarketManager::getInstance().setCredentials(uname, pwd);
        std::cout << "User registered successfully!" << std::endl;
    }
    else if (type == "TaskManager")
    {
        if (TaskManager::isRegistered())
        {
            std::cout << "A TaskManager already exists." << std::endl;
            return;
        }
        TaskManager::getInstance().setCredentials(uname, pwd);
        std::cout << "User registered successfully!" << std::endl;
    }
    else
    {
        std::cout << "Unknown user type. Use: Player, MarketManager, TaskManager." << std::endl;
    }
}

void Game::cmdLogin(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "Usage: login <username> <password>" << std::endl;
        return;
    }
    const std::string& uname = args[1];
    const std::string& pwd = args[2];

    // Check players
    for (const auto& p : players)
    {
        if (p->getUsername() == uname)
        {
            // validate password via changePassword dry-run approach –
            // instead, expose a check method or compare directly.
            // We access password through a helper on User base.
            // Since password is protected, we add a validate helper on User.
            if (!p->validatePassword(pwd))
            {
                std::cout << "Incorrect password." << std::endl;
                return;
            }
            currentUser = p.get();
            std::cout << "Welcome, " << uname << "!" << std::endl;
            return;
        }
    }
    // Check MarketManager
    if (MarketManager::isRegistered())
    {
        auto& mm = MarketManager::getInstance();
        if (mm.getUsername() == uname)
        {
            if (!mm.validatePassword(pwd))
            {
                std::cout << "Incorrect password." << std::endl;
                return;
            }
            currentUser = &mm;
            std::cout << "Welcome, " << uname << "!" << std::endl;
            return;
        }
    }
    // Check TaskManager
    if (TaskManager::isRegistered())
    {
        auto& tm = TaskManager::getInstance();
        if (tm.getUsername() == uname)
        {
            if (!tm.validatePassword(pwd))
            {
                std::cout << "Incorrect password." << std::endl;
                return;
            }
            currentUser = &tm;
            std::cout << "Welcome, " << uname << "!" << std::endl;
            return;
        }
    }

    std::cout << "User not found." << std::endl;
}

// ═══════════════════════════════════════════════════════════════════════════
//  SHARED COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::cmdLogout()
{
    std::cout << "Goodbye, " << currentUser->getUsername() << "!" << std::endl;
    currentUser = nullptr;
    printHeader();
}

void Game::cmdProfileInfo()
{
    std::cout << currentUser->profileInfo() << std::endl;
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
//  PLAYER COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::cmdCheckBalance()
{
    Player* p = currentPlayer();
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2)
        << p->getBalance() << std::endl;
}

void Game::cmdCheckScore()
{
    std::cout << "Current Score: " << currentPlayer()->getScore() << std::endl;
}

void Game::cmdCheckBarn()
{
    currentPlayer()->getBarn().display();
}

void Game::cmdCheckFarm()
{
    currentPlayer()->getFarm().display();
}

void Game::cmdExpandCropland()
{
    Player* p = currentPlayer();
    size_t  cap = p->getFarm().getCroplandCapacity();
    int requiredScore = static_cast<int>(cap * 10);
    double cost = 50.0 * cap;

    if (p->getScore() < requiredScore)
    {
        std::cout << "Not enough Score. Need " << requiredScore
            << ", have " << p->getScore() << "." << std::endl;
        return;
    }
    if (p->getBalance() < cost)
    {
        std::cout << "Not enough Balance. Need " << cost
            << ", have " << p->getBalance() << "." << std::endl;
        return;
    }

    p->addBalance(-cost);
    p->getFarm().expandCropland();
    std::cout << "Cropland expanded! New capacity: "
        << p->getFarm().getCroplandCapacity() << std::endl;
}

void Game::cmdExpandFarmland()
{
    Player* p = currentPlayer();
    size_t  cap = p->getFarm().getFarmlandCapacity();
    int requiredScore = static_cast<int>(cap * 10);
    double cost = 50.0 * cap;

    if (p->getScore() < requiredScore)
    {
        std::cout << "Not enough Score. Need " << requiredScore
            << ", have " << p->getScore() << "." << std::endl;
        return;
    }
    if (p->getBalance() < cost)
    {
        std::cout << "Not enough Balance. Need " << cost
            << ", have " << p->getBalance() << "." << std::endl;
        return;
    }

    p->addBalance(-cost);
    p->getFarm().expandFarmland();
    std::cout << "Farmland expanded! New capacity: "
        << p->getFarm().getFarmlandCapacity() << std::endl;
}

void Game::cmdSowPlant(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: sowPlant <seedId>" << std::endl;
        return;
    }
    int seedId = std::stoi(args[1]);
    ProductType type = fromInt(seedId);
    if (type != ProductType::Wheat_Seed && type != ProductType::Corn_Seed)
    {
        std::cout << "Invalid seed id. Use 1 (Wheat Seed) or 2 (Corn Seed)." << std::endl;
        return;
    }
    Player* p = currentPlayer();
    if (p->getFarm().sowPlant(type, p->getBarn()))
        std::cout << "Plants planted successfully!" << std::endl;
    // error message already printed by Farm::sowPlant
}

void Game::cmdAddAnimal(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: addAnimal <animalId>" << std::endl;
        return;
    }
    int animalId = std::stoi(args[1]);
    ProductType type = fromInt(animalId);
    if (type != ProductType::Chicken && type != ProductType::Cow)
    {
        std::cout << "Invalid animal id. Use 3 (Chicken) or 4 (Cow)." << std::endl;
        return;
    }
    Player* p = currentPlayer();
    if (p->getFarm().addAnimal(type, p->getBarn()))
        std::cout << "Animals added successfully!" << std::endl;
}

void Game::cmdHarvest()
{
    Player* p = currentPlayer();
    int     got = p->getFarm().harvest(p->getBarn());
    std::cout << "Harvest completed!" << std::endl;
    if (got > 0)
        std::cout << "Collected " << got << " item(s)." << std::endl;
}

void Game::cmdOpenMarket()
{
    market.showCatalog();
}

void Game::cmdBuyItem(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "Usage: buyItem <productId> <quantity>" << std::endl;
        return;
    }
    int productId = std::stoi(args[1]);
    unsigned qty = static_cast<unsigned>(std::stoi(args[2]));
    ProductType type = fromInt(productId);

    if (type == ProductType::Undefined)
    {
        std::cout << "Invalid product id." << std::endl;
        return;
    }
    Player* p = currentPlayer();
    if (market.buyProduct(type, qty, *p))
        std::cout << "The purchase was successful!" << std::endl;
    else
        std::cout << "Purchase failed. Check product availability or your balance." << std::endl;
}

void Game::cmdSellItem(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "Usage: sellItem <productId> <quantity>" << std::endl;
        return;
    }
    int productId = std::stoi(args[1]);
    unsigned qty = static_cast<unsigned>(std::stoi(args[2]));
    ProductType type = fromInt(productId);

    if (type == ProductType::Undefined)
    {
        std::cout << "Invalid product id." << std::endl;
        return;
    }
    Player* p = currentPlayer();
    if (market.sellProduct(type, qty, *p))
        std::cout << "The sale was successful!" << std::endl;
    else
        std::cout << "Sale failed. Check your barn inventory." << std::endl;
}

void Game::cmdShowTaskBoard()
{
    taskBoard.showTasks();
}

void Game::cmdCompleteTask(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: completeTask <taskId>" << std::endl;
        return;
    }
    int     taskId = std::stoi(args[1]);
    Player* p = currentPlayer();

    Task* task = taskBoard.getTaskById(taskId);
    if (!task)
    {
        std::cout << "Task not found." << std::endl;
        return;
    }

    ProductType required = task->getRequiredProduct().getName();
    unsigned    qty = task->getRequiredQuantity();

    if (!p->getBarn().hasProduct(required, qty))
    {
        std::cout << "Not enough " << toString(required) << " in barn. Need "
            << qty << "." << std::endl;
        return;
    }

    p->getBarn().removeProduct(required, qty);
    p->addBalance(task->getRewardBalance());
    p->addScore(task->getRewardScore());
    taskBoard.removeTask(taskId);

    std::cout << "Task completed! Reward: +" << task->getRewardBalance()
        << " Balance, +" << task->getRewardScore() << " Score." << std::endl;
}

void Game::cmdShowScoreboard()
{
    scoreboard.showScoreboard(allPlayers());
}

// ═══════════════════════════════════════════════════════════════════════════
//  TASKMANAGER COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::cmdShowTasks()
{
    taskBoard.showTasks();
}

void Game::cmdAddTask(const std::vector<std::string>& args)
{
    // addTask <product> <quantity> <rewardBalance> <rewardScore>
    if (args.size() != 5)
    {
        std::cout << "Usage: addTask <product> <quantity> <rewardBalance> <rewardScore>" << std::endl;
        return;
    }
    unsigned qty = static_cast<unsigned>(std::stoi(args[2]));
    double rewardBalance = std::stod(args[3]);
    int rewardScore = std::stoi(args[4]);

    if (currentTaskManager()->addTask(args[1], qty, rewardBalance, rewardScore))
        std::cout << "Task added successfully!" << std::endl;
}

void Game::cmdRemoveTask(const std::vector<std::string>& args)
{
    if (args.size() != 2)
    {
        std::cout << "Usage: removeTask <taskId>" << std::endl;
        return;
    }
    unsigned taskId = static_cast<unsigned>(std::stoi(args[1]));
    if (currentTaskManager()->removeTask(taskId))
        std::cout << "Task removed successfully." << std::endl;
    else
        std::cout << "Task not found." << std::endl;
}

// ═══════════════════════════════════════════════════════════════════════════
//  MARKETMANAGER COMMANDS
// ═══════════════════════════════════════════════════════════════════════════

void Game::cmdRestock(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "Usage: restock <productId> <quantity>" << std::endl;
        return;
    }
    int productId = std::stoi(args[1]);
    unsigned qty = static_cast<unsigned>(std::stoi(args[2]));

    if (currentMarketManager()->restock(productId, qty))
        std::cout << "Restocked successfully." << std::endl;
    else
        std::cout << "Restock failed." << std::endl;
}

void Game::cmdChangePrice(const std::vector<std::string>& args)
{
    if (args.size() != 3)
    {
        std::cout << "Usage: changePrice <productId> <newPrice>" << std::endl;
        return;
    }
    int    productId = std::stoi(args[1]);
    double newPrice = std::stod(args[2]);

    if (currentMarketManager()->changePrice(productId, newPrice))
        std::cout << "Price updated successfully." << std::endl;
    else
        std::cout << "Price change failed." << std::endl;
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
        << "  register <username> <password> <type>\n"
        << "  login <username> <password>\n"
        << "  exit\n";
}

void Game::showHelpPlayer() const
{
    std::cout << "Available commands:\n"
        << "  logout\n"
        << "  profileInfo\n"
        << "  changePassword <oldPassword> <newPassword>\n"
        << "  checkBalance\n"
        << "  checkScore\n"
        << "  checkBarn\n"
        << "  checkFarm\n"
        << "  expandCropland\n"
        << "  expandFarmland\n"
        << "  sowPlant <seedId>\n"
        << "  addAnimal <animalId>\n"
        << "  harvest\n"
        << "  openMarketCatalog\n"
        << "  buyItem <productId> <quantity>\n"
        << "  sellItem <productId> <quantity>\n"
        << "  showTaskBoard\n"
        << "  completeTask <taskId>\n"
		<< "  showScoreboard\n";
}

void Game::showHelpTaskManager() const
{
    std::cout << "Available commands:\n"
        << "  logout\n"
        << "  profileInfo\n"
        << "  changePassword <oldPassword> <newPassword>\n"
        << "  showTasks\n"
        << "  addTask <product> <quantity> <rewardBalance> <rewardScore>\n"
		<< "  removeTask <taskId>\n";
}

void Game::showHelpMarketManager() const
{
    std::cout << "Available commands:\n"
        << "  logout\n"
        << "  profileInfo\n"
        << "  changePassword <oldPassword> <newPassword>\n"
        << "  openMarketCatalog\n"
        << "  restock <productId> <quantity>\n"
		<< "  changePrice <productId> <newPrice>\n";
}