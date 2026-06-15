#include "MarketManager.h"
#include "Market.h"
#include <iostream>

static bool marketManagerRegistered = false;

MarketManager::MarketManager(const std::string& username, const std::string& password)
    : User(username, password)
{
}

MarketManager& MarketManager::getInstance()
{
    static MarketManager instance("__mm__", "__mm__");
    return instance;
}

bool MarketManager::isRegistered()
{
    return marketManagerRegistered;
}

void MarketManager::setCredentials(const std::string& uname, const std::string& pwd)
{
    username = uname;
    password = pwd;
    marketManagerRegistered = true;
}

std::string MarketManager::profileInfo() const
{
    return "Username: " + username + "\nType: MarketManager";
}

void MarketManager::openMarketCatalog() const
{
    Market::getInstance().showCatalog();
}

bool MarketManager::restock(ProductType type, unsigned quantity)
{
    if (type == ProductType::Undefined)
    {
        std::cout << "Invalid product type." << std::endl;
        return false;
    }
    return Market::getInstance().restock(type, quantity);
}

bool MarketManager::changePrice(ProductType type, double newPrice)
{
    if (type == ProductType::Undefined)
    {
        std::cout << "Invalid product type." << std::endl;
        return false;
    }
    return Market::getInstance().changePrice(type, newPrice);
}