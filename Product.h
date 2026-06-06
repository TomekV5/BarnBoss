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
	unsigned requiredCycles;
	unsigned currentCycles;
	ProductType givenItem;
	unsigned givenQuontity;
public:
	Product();
	Product(ProductType name, double price, unsigned cycles, ProductType givenItem, unsigned givenQuontity);
	ProductType getName() const;

	virtual ~Product() = default;
	void advanceCycle();

	bool isReady() const;

	unsigned getCurrentCycles() const;
	unsigned getRequiredCycles() const;

	ProductType getOutputProduct() const;
};
Product fromProductType(ProductType type);