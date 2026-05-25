#pragma once
#include "ProductType.h"
#include "Player.h"
#include "Product.h"
#include <map>
#include <stdexcept>
#include <iostream>
class Market
{
private:
	Market();
	std::map<ProductType, std::pair<unsigned, double>> marketData;
public:
	Market(const Market&) = delete;
	Market operator=(const Market&) = delete;
	static Market& getInstance();
	bool setQuantity(ProductType type, unsigned qty);
	bool setPrice(ProductType type, double price);
	bool buyProduct(ProductType type, unsigned qty, Player& player);
	bool sellProduct(ProductType type, unsigned qty, Player& player);

	/*void addTask(const Product& product, unsigned qty, double rewardBal, int rewardScore);
	bool removeTask(int taskId);

	void showTasks() const;
	Task* getTaskById(int taskId) const;

	void saveToFile(std::ostream& out) const;
	void loadFromFile(std::istream& in);*/
	friend std::ostream& operator<<(std::ostream& os, const Market& market);
};