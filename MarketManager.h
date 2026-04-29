#pragma once
#include "User.h"
#include "Product.h"
class MarketManager :public User
{
private:
	MarketManager() = default;
public:
	MarketManager(const MarketManager&) = delete;
	MarketManager operator=(const MarketManager&) = delete;   // Singleton
	static MarketManager& getInstance();
	void openMarketCatalog(); /*-показва целия каталог с продукти, тяхното количество и цена*/
	bool restock(int productId, int quantity); /*-презарежда даден продукт с дадено количество*/
	bool changePrice(int productId, double newPrice); /*-сменя цената на продукт*/
};

