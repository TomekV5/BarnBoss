#pragma once
#include "Command.h"

class Game;

class LoginCommand : public Command
{
private:
	Game& game;
	std::vector<std::string> args;
public:
	LoginCommand(Game& game, const std::vector<std::string>& args);
	void execute() override;
};

