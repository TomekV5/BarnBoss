#include "Product.h"
unsigned Product::nexId = 0;

Product::Product()
    : id(++nexId), name(ProductType::Undefined), price(0.0), cycles(0), givenItem(ProductType::Undefined), givenQuontity(0)
{
}

Product::Product(ProductType name, double price, unsigned cycles, ProductType givenItem, unsigned givenQuontity)
    : id(++nexId), name(name), price(price), cycles(cycles), givenItem(givenItem), givenQuontity(givenQuontity)
{
}

const ProductType& Product::getName() const
{
	return name;
}

Product fromProductType(ProductType type)
{
	switch (type)
	{
	case ProductType::Wheat:
		return Product(ProductType::Wheat, 5, 6, ProductType::Wheat, 5);
	case ProductType::Corn:
		return Product(ProductType::Corn, 5, 6, ProductType::Corn, 5);
	case ProductType::Egg:
		return Product(ProductType::Egg, 5, 6, ProductType::Chicken, 5);
	case ProductType::Milk:
		return Product(ProductType::Milk, 5, 6, ProductType::Milk, 5);
	case ProductType::Wheat_Seed:
		return Product(ProductType::Wheat_Seed, 5, 6, ProductType::Wheat, 5);
	case ProductType::Corn_Seed:
		return Product(ProductType::Corn_Seed, 5, 6, ProductType::Corn, 1);
	case ProductType::Chicken:
		return Product(ProductType::Chicken, 5, 6, ProductType::Chicken, 1);
	case ProductType::Cow:
		return Product(ProductType::Cow, 5, 6, ProductType::Cow, 1);
	default:
		return Product(ProductType::Undefined, 0, 0, ProductType::Undefined, 0);
	}
}
