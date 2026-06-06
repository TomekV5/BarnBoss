#pragma once
#include "Product.h"
class Animal :public Product
{
public:
    Animal(ProductType animalType);

    unsigned getGivenQuantity() const;
};

