#include "ProfileInfoCommand.h"

ProfileInfoCommand::ProfileInfoCommand(Game& game)
    : game(game)
{
}

void ProfileInfoCommand::execute()
{
	game.profileInfo();
}
