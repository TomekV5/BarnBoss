#include "HarvestCommand.h"

HarvestCommand::HarvestCommand(Player* player) :player(player)
{
}

void HarvestCommand::execute()
{
    int got = player->getFarm().harvest(player->getBarn());
    std::cout << "Harvest completed!\n";
    if (got > 0) {
        std::cout << "Collected " << got << " item(s).\n";
    }
}
