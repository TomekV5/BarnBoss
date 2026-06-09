#include "CheckScoreCommand.h"

CheckScoreCommand::CheckScoreCommand(Player* player):player(player)
{
}

void CheckScoreCommand::execute()
{
	std::cout << "Current Score: " << player->getScore() << std::endl;
}
