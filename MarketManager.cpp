#include "MarketManager.h"
#include "TaskManager.h"

MarketManager::MarketManager(const std::string& username, const std::string& password):User(username,password)
{
}

MarketManager& MarketManager::getInstance()
{
    static MarketManager instance("MarketManager","mmm");
    return instance;
}