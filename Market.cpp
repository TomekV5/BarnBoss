#include "Market.h"
#include "Player.h"
#include <iomanip>
#include <iostream>

Market::Market()
{
    marketData[ProductType::Wheat_Seed] = { 20, 10.0 };
    marketData[ProductType::Corn_Seed] = { 20, 15.0 };
    marketData[ProductType::Chicken] = { 10, 25.0 };
    marketData[ProductType::Cow] = { 5, 50.0 };
    marketData[ProductType::Wheat] = { 20, 15.0 };
    marketData[ProductType::Corn] = { 20, 20.0 };
    marketData[ProductType::Egg] = { 15, 30.0 };
    marketData[ProductType::Milk] = { 10, 60.0 };
}

Market& Market::getInstance()
{
    static Market instance;
    return instance;
}

bool Market::restock(ProductType type, unsigned qty)
{
    auto it = marketData.find(type);
    if (it == marketData.end()) return false;
    it->second.first += qty;
    return true;
}

bool Market::changePrice(ProductType type, double newPrice)
{
    auto it = marketData.find(type);
    if (it == marketData.end() || newPrice <= 0) return false;
    it->second.second = newPrice;
    return true;
}

bool Market::buyProduct(ProductType type, unsigned qty, Player& player)
{
    auto it = marketData.find(type);
    if (it == marketData.end()) return false;
    if (it->second.first < qty) return false; // not enough stock
    double cost = it->second.second * qty;
    if (player.getBalance() < cost) return false; // can't afford

    it->second.first -= qty;
    player.addBalance(-cost);
    player.getBarn().addProduct(type, qty);
    return true;
}

bool Market::sellProduct(ProductType type, unsigned qty, Player& player)
{
    auto it = marketData.find(type);
    if (it == marketData.end())                      return false;
    if (!player.getBarn().hasProduct(type, qty))     return false;

    double revenue = it->second.second * qty;
    player.getBarn().removeProduct(type, qty);
    it->second.first += qty;        // product goes back to market
    player.addBalance(revenue);
    return true;
}

void Market::showCatalog() const
{
    std::cout << "=== MARKET CATALOG ===" << std::endl;
    const ProductType order[] = {
        ProductType::Wheat_Seed, ProductType::Corn_Seed,
        ProductType::Chicken,    ProductType::Cow,
        ProductType::Wheat,      ProductType::Corn,
        ProductType::Egg,        ProductType::Milk
    };
    int idx = 1;
    for (ProductType t : order)
    {
        const auto& entry = marketData.at(t);
        std::cout << idx++ << ". "
            << std::left << std::setw(12) << toString(t)
            << "| Qty: " << std::setw(4) << entry.first
            << "| Price: " << entry.second
            << std::endl;
    }
}

void Market::saveToFile(std::ostream& out) const
{
    out << marketData.size() << "\n";
    for (const auto& e : marketData)
        out << toInt(e.first) << " "
        << e.second.first << " "
        << e.second.second << "\n";
}

void Market::loadFromFile(std::istream& in)
{
    size_t count;
    in >> count;
    for (size_t i = 0; i < count; i++)
    {
        int typeInt;
        unsigned qty;
        double price;
        in >> typeInt >> qty >> price;
        ProductType type = fromInt(typeInt);
        marketData[type] = { qty, price };
    }
}

std::ostream& operator<<(std::ostream& os, const Market& m)
{
    m.showCatalog();
    return os;
}
void Market::reset()
{
    marketData.clear();
    marketData[ProductType::Wheat_Seed] = { 20, 10.0 };
    marketData[ProductType::Corn_Seed] = { 20, 15.0 };
    marketData[ProductType::Chicken] = { 10, 25.0 };
    marketData[ProductType::Cow] = { 5,  50.0 };
    marketData[ProductType::Wheat] = { 20, 15.0 };
    marketData[ProductType::Corn] = { 20, 20.0 };
    marketData[ProductType::Egg] = { 15, 30.0 };
    marketData[ProductType::Milk] = { 10, 60.0 };
}