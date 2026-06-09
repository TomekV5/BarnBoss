#include "ExpandCroplandCommand.h"

ExpandCroplandCommand::ExpandCroplandCommand(Player* player):player(player)
{
    size_t capacity = player->getFarm().getCroplandCapacity();
    size_t requiredScore = capacity * 10;
    cost = 50.0 * capacity;
    if (player->getScore() < requiredScore)
    {
        throw std::invalid_argument("Not enough Score. Need " + std::to_string(requiredScore)
            + ", have " + std::to_string(player->getScore()) + ".");
        return;
    }
    if (player->getBalance() < cost)
    {
        throw std::invalid_argument("Not enough Balance. Need " + std::to_string(cost)
            + ", have " + std::to_string(player->getBalance()) + ".");
    }
}

void ExpandCroplandCommand::execute()
{
    player->addBalance(-cost);
    player->getFarm().expandCropland();
    std::cout << "Cropland expanded! New capacity: "
        << player->getFarm().getCroplandCapacity() << std::endl;
}
