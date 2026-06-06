#include "Animal.h"

Animal::Animal(ProductType animalType) : Product()
{
    switch (animalType)
    {
    case ProductType::Chicken:
        name = ProductType::Chicken;
        price = 25.0;
        requiredCycles = 3;
        givenItem = ProductType::Egg;
        givenQuontity = 1;
        break;

    case ProductType::Cow:
        name = ProductType::Cow;
        price = 50.0;
        requiredCycles = 5;
        givenItem = ProductType::Milk;
        givenQuontity = 1;
        break;

    default:
        throw std::invalid_argument("Invalid animal type for Animal.");
    }
}

unsigned Animal::getGivenQuantity() const
{
    return givenQuontity;
}