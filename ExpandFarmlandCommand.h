#pragma once
#include "Command.h"
#include "Player.h"
class ExpandFarmlandCommand: public Command
{
private:
	Player* player;
	double cost;
public:
	ExpandFarmlandCommand(Player* player);
	void execute() override;
};

