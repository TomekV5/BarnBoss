#pragma once
#include "Command.h"
#include "Game.h"
class ProfileInfoCommand :public Command
{
private:
	Game& game;
public:
	ProfileInfoCommand(Game& game);
	void execute() override;
};

