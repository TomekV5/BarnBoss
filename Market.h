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
    // ProductType -> { quantity, price }
    std::map<ProductType, std::pair<unsigned, double>> marketData;

public:
    Market(const Market&) = delete;
    Market& operator=(const Market&) = delete;

    static Market& getInstance();

    // ── MarketManager operations ──────────────────────────────────────────
    bool restock(ProductType type, unsigned qty);
    bool changePrice(ProductType type, double newPrice);

    // ── Player operations ─────────────────────────────────────────────────
    bool buyProduct(ProductType type, unsigned qty, Player& player);
    bool sellProduct(ProductType type, unsigned qty, Player& player);

    // ── Display ───────────────────────────────────────────────────────────
    void showCatalog() const;

    // ── Save / load ───────────────────────────────────────────────────────
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);

    // kept for legacy streaming use
    friend std::ostream& operator<<(std::ostream& os, const Market& m);
};