#include "Barn.h"
#include <iostream>

Barn::Barn()
{
    // Initialise every known product type to 0
    inventory[ProductType::Wheat] = 0;
    inventory[ProductType::Corn] = 0;
    inventory[ProductType::Egg] = 0;
    inventory[ProductType::Milk] = 0;
    inventory[ProductType::Wheat_Seed] = 0;
    inventory[ProductType::Corn_Seed] = 0;
    inventory[ProductType::Chicken] = 0;
    inventory[ProductType::Cow] = 0;
}

bool Barn::addProduct(ProductType type, unsigned quantity)
{
    inventory[type] += quantity;
    return true;
}

bool Barn::removeProduct(ProductType type, unsigned quantity)
{
    auto it = inventory.find(type);
    if (it == inventory.end() || it->second < quantity)
        return false;

    it->second -= quantity;
    return true;
}

unsigned Barn::getQuantity(ProductType type) const
{
    auto it = inventory.find(type);
    if (it == inventory.end())
        return 0;
    return it->second;
}

bool Barn::hasProduct(ProductType type, unsigned quantity) const
{
    return getQuantity(type) >= quantity;
}

void Barn::display() const
{
    std::cout << "=== BARN ===" << std::endl;
    std::cout << "Wheat Seed: " << getQuantity(ProductType::Wheat_Seed) << std::endl;
    std::cout << "Corn Seed:  " << getQuantity(ProductType::Corn_Seed) << std::endl;
    std::cout << "Chicken:    " << getQuantity(ProductType::Chicken) << std::endl;
    std::cout << "Cow:        " << getQuantity(ProductType::Cow) << std::endl;
    std::cout << "Wheat:      " << getQuantity(ProductType::Wheat) << std::endl;
    std::cout << "Corn:       " << getQuantity(ProductType::Corn) << std::endl;
    std::cout << "Egg:        " << getQuantity(ProductType::Egg) << std::endl;
    std::cout << "Milk:       " << getQuantity(ProductType::Milk) << std::endl;
}

void Barn::saveToFile(std::ostream& out) const
{
    out << inventory.size() << "\n";
    for (const auto& entry : inventory)
        out << toInt(entry.first) << " " << entry.second << "\n";
}

void Barn::loadFromFile(std::istream& in)
{
    inventory.clear();
    size_t count;
    in >> count;
    for (size_t i = 0; i < count; i++)
    {
        int typeInt;
        unsigned qty;
        in >> typeInt >> qty;
        inventory[fromInt(typeInt)] = qty;
    }
}