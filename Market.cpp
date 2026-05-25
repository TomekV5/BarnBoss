#include "Market.h"
Market::Market()
{
	marketData[ProductType::Wheat] = { 20, 15.0 };
	marketData[ProductType::Corn] = { 20, 20.0 };
	marketData[ProductType::Egg] = { 15, 30.0 };
	marketData[ProductType::Milk] = { 10, 60.0 };
	marketData[ProductType::Wheat_Seed] = { 20, 10.0 };
	marketData[ProductType::Corn_Seed] = { 20, 15.0 };
	marketData[ProductType::Chicken] = { 10, 25.0 };
	marketData[ProductType::Cow] = { 5, 50.0 };
}
Market& Market::getInstance()
{
	static Market instance;
	return instance;
}

bool Market::setQuantity(ProductType type, unsigned qty)
{
	try {
		marketData.at(type).first = qty;
		return true;
	}
	catch (std::out_of_range&) {
		return false;
	}
}

bool Market::setPrice(ProductType type, double price)
{
	try {
		marketData.at(type).second = price;
		return true;
	}
	catch (std::out_of_range&) {
		return false;
	}
}
bool Market::buyProduct(ProductType type, unsigned qty, Player& player)
{
	try {
		const auto& data = marketData.at(type);
		if (data.first < qty)
			return false; // Not enough quantity in market
		double totalCost = data.second * qty;
		if (player.getBalance() < totalCost)
			return false; // Player can't afford
		// Update market and player
		marketData.at(type).first -= qty;
		player.setBalance(player.getBalance() - totalCost);
		player.getBarn().addProduct(fromProductType(type), qty);
		return true;
	}
	catch (std::out_of_range&) {
		return false;
	}
}
bool Market::sellProduct(ProductType type, unsigned qty, Player& player)
{
	return false;
}
std::ostream& operator<<(std::ostream& os, const Market& market)
{
	for (const auto& entry : market.marketData)
	{
		os << toString(entry.first) << " "
			<< entry.second.first << " "
			<< entry.second.second << std::endl;
	}
	return os;
}
