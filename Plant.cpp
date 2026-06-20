#include "Plant.h"
#include <stdexcept>

Plant::Plant(ProductType seedType) : Product()
{
    switch (seedType)
    {
    case ProductType::Wheat_Seed:
        name = ProductType::Wheat_Seed;
        price = 10.0;
        requiredCycles = 3;
        givenItem = ProductType::Wheat;
        givenQuontity = 1;
        break;

    case ProductType::Corn_Seed:
        name = ProductType::Corn_Seed;
        price = 15.0;
        requiredCycles = 4;
        givenItem = ProductType::Corn;
        givenQuontity = 1;
        break;

    default:
        throw std::invalid_argument("Invalid seed type for Plant.");
    }
}
