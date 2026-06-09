#include "CheckFarmCommand.h"

CheckFarmCommand::CheckFarmCommand(Player* player) :player(player)
{
}

void CheckFarmCommand::execute()
{
	player->getFarm().display();
}
