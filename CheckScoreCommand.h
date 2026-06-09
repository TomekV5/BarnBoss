#pragma once
#include "Command.h"
#include "Player.h"
class CheckScoreCommand : public Command
{
private:
	Player* player;
public:
	CheckScoreCommand(Player* player);
	void execute() override;
};

