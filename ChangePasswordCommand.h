#pragma once
#include "Command.h"
#include "Game.h"
#include "User.h"
class ChangePasswordCommand :public Command
{
	private:
	User* user;
	std::vector<std::string> args;
public:
	ChangePasswordCommand(User* user, const std::vector<std::string>& args);
	void execute() override;
};

