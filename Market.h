#pragma once
#include "ProductType.h"
class Market
{
private:
	Market()=default;
	//std::vector<std::unique_ptr<Task>> tasks;
public:
	Market(const Market&) = delete;
	Market operator=(const Market&) = delete;
	static Market& getInstance();
	bool setQuantity(ProductType type, unsigned qty);
	bool setPrice(ProductType type, unsigned price);

	/*void addTask(const Product& product, unsigned qty, double rewardBal, int rewardScore);
	bool removeTask(int taskId);

	void showTasks() const;
	Task* getTaskById(int taskId) const;

	void saveToFile(std::ostream& out) const;
	void loadFromFile(std::istream& in);*/

};

