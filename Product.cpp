#include "Product.h"
unsigned Product::nexId = 0;
Product::Product()
{
	id = nexId++;
	name = ProductType::Undefined;
	price = 0.0;
	cycles = 0;
	givenItem = ProductType::Undefined;
	givenQuontity = 0;
}

Product::Product(ProductType name, double price, unsigned cycles, ProductType givenItem, unsigned givenQuontity)
{
	id = nexId++;
	this->name = name;
	this->price = price;
	this->cycles = cycles;
	this->givenItem = givenItem;
	this->givenQuontity = givenQuontity;
}
