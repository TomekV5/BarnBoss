#include "BuyItemCommand.h"

BuyItemCommand::BuyItemCommand(Player* player, Market& market, const std::vector<std::string>& args) :player(player), market(market), args(args)
{
	if (args.size() != 3)
	{
		throw std::invalid_argument("Usage: buyItem <productName> <quantity>");
	}
	type = fromString(args[1]);
	quantity = static_cast<unsigned>(std::stoi(args[2]));
	if (type == ProductType::Undefined)
	{
		throw std::invalid_argument("Invalid product name. Use 'Wheat', 'Corn', 'Milk', etc.");
	}
}

void BuyItemCommand::execute()
{
	if (market.buyProduct(type, quantity, *player))
	{
		std::cout << "The purchase was successful!" << std::endl;
	}
	else {
		std::cout << "Purchase failed. Check product availability or your balance." << std::endl;
	}
}
