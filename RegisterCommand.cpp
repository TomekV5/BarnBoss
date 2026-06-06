#include "RegisterCommand.h"

RegisterCommand::RegisterCommand(Game& game, const std::vector<std::string>& args)
    : game(game), args(args)
{
}

void RegisterCommand::execute()
{
    if (args.size() != 4)
    {
        std::cout << "Usage: register <username> <password> <type>\n";
        return;
    }

    const std::string& username = args[1];
    const std::string& password = args[2];
    const std::string& type = args[3];

    if (password.size() < 3)
    {
        std::cout << "Password must be at least 3 characters.\n";
        return;
    }

    game.registerUser(username, password, type);
}
