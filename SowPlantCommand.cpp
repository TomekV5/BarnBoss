#include "SowPlantCommand.h"

SowPlantCommand::SowPlantCommand(Player* player, const std::vector<std::string>& args) :player(player), args(args)
{
    if (args.size() != 2)
    {
       throw std::invalid_argument("Usage: sowPlant <seedName>");
    }
    type = fromString(args[1]);
    if (type != ProductType::Wheat_Seed && type != ProductType::Corn_Seed)
    {
        throw std::invalid_argument("Invalid seed name. Use 'Wheat_Seed' or 'Corn_Seed'.");
    }
}

void SowPlantCommand::execute()
{
    if (player->getFarm().sowPlant(type, player->getBarn())) {
        std::cout << "Plants planted successfully!" << std::endl;
    }  
}
