#include "ProductType.h"
std::string toString(ProductType type)
{
	switch (type)
	{
	case ProductType::Wheat:
		return "Wheat";
	case ProductType::Corn:
		return "Corn";
	case ProductType::Egg:
		return "Egg";
	case ProductType::Milk:
		return "Milk";
	case ProductType::Wheat_Seed:
		return "Wheat_Seed";
	case ProductType::Corn_Seed:
		return "Corn_Seed";
	case ProductType::Chicken:
		return "Chicken";
	case ProductType::Cow:
		return "Cow";
	default:
		return "Undefined";
	}
}

ProductType fromInt(int value)
{
	switch (value)
	{
		case 1:
			return ProductType::Wheat;
		case 2:
			return ProductType::Corn;
		case 3:
			return ProductType::Egg;
		case 4:
			return ProductType::Milk;
		case 5:
			return ProductType::Wheat_Seed;
		case 6:
			return ProductType::Corn_Seed;
		case 7:
			return ProductType::Chicken;
		case 8:
			return ProductType::Cow;
	default:
		return ProductType::Undefined;
	}
}

int toInt(ProductType type)
{
	switch (type)
	{
	case ProductType::Wheat:
		return 1;
	case ProductType::Corn:
		return 2;
	case ProductType::Egg:
		return 3;
	case ProductType::Milk:
		return 4;
	case ProductType::Wheat_Seed:
		return 5;
	case ProductType::Corn_Seed:
		return 6;
	case ProductType::Chicken:
		return 7;
	case ProductType::Cow:
		return 8;
	default:
		return 0;
	}
}

ProductType fromString(const std::string& str)
{
	if (str == "Wheat") return ProductType::Wheat;
	else if (str == "Corn") return ProductType::Corn;
	else if (str == "Egg") return ProductType::Egg;
	else if (str == "Milk") return ProductType::Milk;
	else if (str == "Wheat_Seed") return ProductType::Wheat_Seed;
	else if (str == "Corn_Seed") return ProductType::Corn_Seed;
	else if (str == "Chicken") return ProductType::Chicken;
	else if (str == "Cow") return ProductType::Cow;
	else return ProductType::Undefined;
}

