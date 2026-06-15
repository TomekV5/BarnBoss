#include "AdvanceCycleCommand.h"

AdvanceCycleCommand::AdvanceCycleCommand(Player* player) :player(player)
{
}

void AdvanceCycleCommand::execute()
{
	player->getFarm().advanceCycles();
}
