#include "ExpandFarmlandCommand.h"

ExpandFarmlandCommand::ExpandFarmlandCommand(Player* player):player(player)
{
    size_t  cap = player->getFarm().getFarmlandCapacity();
    size_t requiredScore = cap * 10;
    cost = 50.0 * cap;
    if (player->getScore() < requiredScore)
    {
        throw std::invalid_argument("Not enough Score. Need " + std::to_string(requiredScore)
            + ", have " + std::to_string(player->getScore()) + ".");
    }
    if (player->getBalance() < cost)
    {
        throw std::invalid_argument("Not enough Balance. Need " + std::to_string(cost)
            + ", have " + std::to_string(player->getBalance()) + ".");
    }
}

void ExpandFarmlandCommand::execute()
{
    player->addBalance(-cost);
    player->getFarm().expandFarmland();
    std::cout << "Farmland expanded! New capacity: "
        << player->getFarm().getFarmlandCapacity() << std::endl;
}
