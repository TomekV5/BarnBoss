#pragma once
#include "Product.h"
class Task
{
private:
	static unsigned nextId;
	unsigned id;
	Product	requiredProduct;
	unsigned requiredQuantity;
	int rewardBalance;
	int	rewardScore;
};