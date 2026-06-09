#pragma once
#include "Command.h"
#include "Player.h"
class CheckBarnCommand: public Command
{
private:
	Player* player;
public:
	CheckBarnCommand(Player* player);
	void execute() override;
};

