#pragma once
#include "Command.h"
#include "Player.h"
class ExpandCroplandCommand : public Command
{
private:
	Player* player;
	double cost;
public:
	ExpandCroplandCommand(Player* player);
	void execute() override;
};

