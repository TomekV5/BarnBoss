#pragma once
#include "Command.h"
#include "Player.h"
class AddAnimalCommand :public Command
{
private:
	Player* player;
	ProductType type;
	std::vector<std::string> args;
public:
	AddAnimalCommand(Player* player, const std::vector<std::string>& args);
	void execute() override;
};

