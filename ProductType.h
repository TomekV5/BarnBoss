#pragma once
#include <string>

enum class ProductType
{
	Undefined,
	Wheat,
	Corn,
	Egg,
	Milk,
	Wheat_Seed,
	Corn_Seed,
	Chicken,
	Cow
};

std::string toString(ProductType type);
ProductType fromInt(int value);
int toInt(ProductType type);
ProductType fromString(const std::string& str);
// Fix: Forward declare Product before using it as a return type