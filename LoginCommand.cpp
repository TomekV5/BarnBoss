#include "LoginCommand.h"
#include "Game.h"

LoginCommand::LoginCommand(Game& game, const std::vector<std::string>& args) :game(game), args(args)
{
    if (args.size() != 3)
    {
        throw std::invalid_argument("Usage: login <username> <password>");
    }
}

void LoginCommand::execute()
{
    const std::string& username = args[1];
    const std::string& password = args[2];

    game.loginUser(username, password);
}
