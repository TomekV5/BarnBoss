#pragma once
#include "Command.h"
#include "Game.h"
class ProfileInfoCommand :public Command
{
private:
	User* user;
public:
	ProfileInfoCommand(User* user);
	void execute() override;
};

