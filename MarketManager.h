#pragma once
#include "User.h"
#include "ProductType.h"

class MarketManager : public User
{
private:
    MarketManager(const std::string& username, const std::string& password);

public:
    MarketManager(const MarketManager&) = delete;
    MarketManager& operator=(const MarketManager&) = delete;

    static MarketManager& getInstance();
    static bool isRegistered();

    void setCredentials(const std::string& username, const std::string& password);

    std::string profileInfo() const override;

    void openMarketCatalog() const;
    bool restock(ProductType type, unsigned quantity);
    bool changePrice(ProductType type, double newPrice);
    void reset();
};