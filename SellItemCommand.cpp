#include "SellItemCommand.h"

SellItemCommand::SellItemCommand(Player* player, Market& market, const std::vector<std::string>& args):
    player(player),
    market(market),
	args(args)
{
    if (args.size() != 3)
    {
        throw std::invalid_argument("Usage: sellItem <productName> <quantity>");
    }
    type = fromString(args[1]);
    quantity = static_cast<unsigned>(std::stoi(args[2]));
    if (type == ProductType::Undefined)
    {
        throw std::invalid_argument("Invalid product name. Use 'Wheat', 'Corn', 'Milk', etc.");
    }
}

void SellItemCommand::execute()
{
    if (market.sellProduct(type, quantity, *player))
        std::cout << "The sale was successful!" << std::endl;
    else
        std::cout << "Sale failed. Check your barn inventory." << std::endl;
}
