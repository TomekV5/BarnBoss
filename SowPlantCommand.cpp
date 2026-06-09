#include "SowPlantCommand.h"

SowPlantCommand::SowPlantCommand(Player* player, const std::vector<std::string>& args) :player(player), args(args)
{
    if (args.size() != 2)
    {
       throw std::invalid_argument("Usage: sowPlant <seedId>");
    }
    int seedId = std::stoi(args[1]);
    type = fromInt(seedId);
    if (type != ProductType::Wheat_Seed && type != ProductType::Corn_Seed)
    {
        throw std::invalid_argument("Invalid seed id. Use 1 (Wheat Seed) or 2 (Corn Seed).");
    }
}

void SowPlantCommand::execute()
{
    if (player->getFarm().sowPlant(type, player->getBarn())) {
        std::cout << "Plants planted successfully!" << std::endl;
    }  
}
