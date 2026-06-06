#include "LogOutCommand.h"

LogOutCommand::LogOutCommand(Game& game) :game(game)
{
}

void LogOutCommand::execute()
{
	game.logout();
}
