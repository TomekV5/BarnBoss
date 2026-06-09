#include "CheckBarnCommand.h"

CheckBarnCommand::CheckBarnCommand(Player* player):player(player)
{
}

void CheckBarnCommand::execute()
{
	player->getBarn().display();
}
