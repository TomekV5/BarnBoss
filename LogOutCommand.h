#pragma once
#include "Command.h"
#include "Game.h"
class LogOutCommand :public Command
{
private:
	Game& game;
public:
	LogOutCommand(Game& game);
	void execute() override;
};