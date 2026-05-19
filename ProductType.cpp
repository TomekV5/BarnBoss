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

const ProductType& fromInt(int value)
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

