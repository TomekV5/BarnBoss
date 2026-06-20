#pragma once
#include "ProductType.h"
#include <map>
#include <iostream>

// Forward declaration to avoid circular include (Market <-> Player)
class Player;

class Market
{
private:
    Market();
    std::map<ProductType, std::pair<unsigned, double>> marketData;

public:
    Market(const Market&) = delete;
    Market& operator=(const Market&) = delete;

    static Market& getInstance();

    bool restock(ProductType type, unsigned qty);
    bool changePrice(ProductType type, double newPrice);

    bool buyProduct(ProductType type, unsigned qty, Player& player);
    bool sellProduct(ProductType type, unsigned qty, Player& player);

    void showCatalog() const;

    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
    void reset();

    friend std::ostream& operator<<(std::ostream& os, const Market& m);
};