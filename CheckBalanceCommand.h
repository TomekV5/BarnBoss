#pragma once
#include "Command.h"
#include "Player.h"
class CheckBalanceCommand : public Command
{
private:
	Player* player;
public:
	CheckBalanceCommand(Player* player);
	void execute() override;
};

