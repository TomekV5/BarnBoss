#pragma once
#include "Command.h"
#include "Player.h"
class SowPlantCommand :public Command
{
private:
	Player* player;
	std::vector<std::string> args;
	ProductType type;
public:
	SowPlantCommand(Player* player, const std::vector<std::string>& args);
	void execute() override;
};