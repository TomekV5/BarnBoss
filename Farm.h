#pragma once
#include "Animal.h"
#include "Plant.h"
#include <vector>
class Farm
{
private:
	std::vector<Plant> cropland;
	std::vector<Animal> farmland;
	size_t croplandCapacity;
	size_t farmlandCapacity;
};

