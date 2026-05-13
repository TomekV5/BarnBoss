#pragma once
#include <iostream>
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
class Product
{
protected:
	static unsigned nexId;
	unsigned id;
	ProductType name;
	double price;
	unsigned cycles;
	ProductType givenItem;
	unsigned givenQuontity;
public:
	Product();
	Product(ProductType name, double price, unsigned cycles, ProductType givenItem, unsigned givenQuontity);
};