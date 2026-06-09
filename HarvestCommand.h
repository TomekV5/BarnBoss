#pragma once
#include "Command.h"
#include "Player.h"
class HarvestCommand : public Command
{
private:
	Player* player;
public:
	HarvestCommand(Player* player);
	void execute() override;
};

