#include "Game.h"
#include <fstream>
#include <sstream>

Game::Game()
{
	currentUser = nullptr;
	marketManager;

	taskBoard = &TaskBoard::getInstance();
	scoreboard = &ScoreBoard::getInstance();
	market = &Market::getInstance();
	running = false;
}

Game::~Game()
{
	delete currentUser;
	delete market;
	delete taskBoard;
	delete scoreboard;

}
//void Game::LoadFromFile(const std::string& filename)
//{
//    std::ifstream inFile(filename);
//
//    if (!inFile.is_open())
//    {
//        std::cout << "No save file found. Starting new game.\n";
//
//        return;
//    }
//
//    // Clear old data
//    users.clear();
//
//    delete market;
//    delete taskBoard;
//    delete scoreboard;
//
//    currentUser = nullptr;
//
//    size_t usersCount;
//    inFile >> usersCount;
//
//    for (size_t i = 0; i < usersCount; i++)
//    {
//        std::string type;
//        std::string username;
//        std::string password;
//
//        inFile >> type >> username >> password;
//
//        if (type == "Player")
//        {
//            int balance;
//            int score;
//
//            inFile >> balance >> score;
//
//            auto player = std::make_unique<Player>(username, password);
//
//            player->setBalance(balance);
//            player->setScore(score);
//
//            // Load Barn
//            int barnItemsCount;
//            inFile >> barnItemsCount;
//
//            for (int j = 0; j < barnItemsCount; j++)
//            {
//                int productId;
//                int quantity;
//
//                inFile >> productId >> quantity;
//
//                player->getBarn().addProduct(
//                    fromProductType(fromInt(productId)),
//                    quantity
//                );
//            }
//
//            users.push_back(std::move(player));
//        }
//		else if (type == "TaskManager")//problem: only one task manager and market manager allowed, but we can have multiple of them in the file
//        {
//            /*users.push_back(
//                std::make_unique<TaskManager>(username, password)
//            );*/
//        }
//        else if (type == "MarketManager")
//        {
//            /*users.push_back(
//                std::make_unique<MarketManager>(username, password)
//            );*/
//        }
//    }
//
//    // Load Market
//    int marketItems;
//
//    inFile >> marketItems;
//
//    for (int i = 0; i < marketItems; i++)
//    {
//        int productId;
//        int quantity;
//        int price;
//
//        inFile >> productId >> quantity >> price;
//
//        market->setQuantity(
//            static_cast<ProductType>(productId),
//            quantity
//        );
//
//        market->setPrice(
//            static_cast<ProductType>(productId),
//            price
//        );
//    }
//
//    // Load Tasks
//    int tasksCount;
//
//    inFile >> tasksCount;
//
//    for (int i = 0; i < tasksCount; i++)
//    {
//        int id;
//        int productId;
//        int quantity;
//        int rewardBalance;
//        int rewardScore;
//
//        inFile >> id
//            >> productId
//            >> quantity
//            >> rewardBalance
//            >> rewardScore;
//
//		taskBoard->addTask(Product(fromInt(productId),5,5,ProductType::Undefined,5), quantity, rewardBalance, rewardScore);
//    }
//
//    inFile.close();
//
//    std::cout << "Game loaded successfully.\n";
//}

void Game::CreateNewGame()
{
	running = true;
}
