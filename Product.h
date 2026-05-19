#pragma once
#include <iostream>
#include "ProductType.h"
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
	const ProductType& getName() const;
};
Product fromProductType(ProductType type);