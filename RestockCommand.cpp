#include "RestockCommand.h"

RestockCommand::RestockCommand(MarketManager& marketManager, const std::vector<std::string>& args):
	marketManager(marketManager),
	args(args)
{
	if (args.size() != 3)
	{
		throw std::invalid_argument("Usage: restock <productName> <quantity>");
	}
	type = fromString(args[1]);
	quantity = static_cast<unsigned>(std::stoi(args[2]));
}

void RestockCommand::execute()
{
	if (marketManager.restock(type, quantity))
		std::cout << "Restocked successfully." << std::endl;
	else
		std::cout << "Restock failed." << std::endl;
}