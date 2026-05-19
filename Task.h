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
public:
	Task(const Product& requiredProduct, unsigned requiredQuantity, int rewardBalance, int rewardScore);
	const unsigned& getId() const;
	const Product& getRequiredProduct() const;
	const unsigned& getRequiredQuantity() const;
	const int& getRewardBalance() const;
	const int& getRewardScore() const;
};