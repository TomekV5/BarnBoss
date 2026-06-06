#include "LoginCommand.h"
#include "Game.h"

LoginCommand::LoginCommand(Game& game, const std::vector<std::string>& args) :game(game), args(args)
{
}

void LoginCommand::execute()
{
    if (args.size() != 3)
    {
        std::cout << "Usage: login <username> <password>" << std::endl;
        return;
    }
    const std::string& username = args[1];
    const std::string& password = args[2];

    game.loginUser(username, password);
}
