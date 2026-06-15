#include "ChangePriceCommand.h"

ChangePriceCommand::ChangePriceCommand(MarketManager& manager, const std::vector<std::string>& args):
	marketManager(manager),
	args(args)
{
	if (args.size() != 3) {
		throw std::invalid_argument("Usage: changePrice <productName> <newPrice>");
	}
	type = fromString(args[1]);
	newPrice = std::stod(args[2]);
}

void ChangePriceCommand::execute()
{
	if (marketManager.changePrice(type, newPrice)) {
		std::cout << "Price updated successfully." << std::endl;
	} else {
		std::cout << "Price change failed." << std::endl;
	}
}