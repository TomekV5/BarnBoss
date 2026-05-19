#include "Task.h"
unsigned Task::nextId = 1;
Task::Task(const Product& requiredProduct, unsigned requiredQuantity, int rewardBalance, int rewardScore) :requiredProduct(requiredProduct), requiredQuantity(requiredQuantity), rewardBalance(rewardBalance), rewardScore(rewardScore)
{
	id = nextId++;
}

const unsigned& Task::getId() const
{
	return id;
}

const Product& Task::getRequiredProduct() const
{
	return requiredProduct;
}

const unsigned& Task::getRequiredQuantity() const	
{
	return requiredQuantity;
}

const int& Task::getRewardBalance() const
{
	return rewardBalance;
}

const int& Task::getRewardScore() const
{
	return rewardScore;
}