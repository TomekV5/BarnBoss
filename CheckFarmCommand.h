#pragma once
#include "Command.h"
#include "Player.h"
class CheckFarmCommand : public Command
{
private:
	Player* player;
public:
	CheckFarmCommand(Player* player);
	void execute() override;
};

