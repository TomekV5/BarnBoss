#include "Market.h"
Market& Market::getInstance()
{
	static Market instance;
	return instance;
}