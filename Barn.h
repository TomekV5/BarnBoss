#pragma once
#include "ProductType.h"
#include <map>
#include <iostream>

class Barn
{
private:
    // Maps ProductType -> quantity stored
    std::map<ProductType, unsigned> inventory;

public:
    Barn();

    // Add quantity of a product (by type). Returns true always.
    bool addProduct(ProductType type, unsigned quantity);

    // Remove quantity of a product. Returns false if not enough stock.
    bool removeProduct(ProductType type, unsigned quantity);

    // Returns quantity of a product (0 if not present).
    unsigned getQuantity(ProductType type) const;

    // Returns true if at least 'quantity' units of type are available.
    bool hasProduct(ProductType type, unsigned quantity) const;

    // Print all products and their quantities.
    void display() const;

    // Save/load support
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};