#include "RegisterCommand.h"

RegisterCommand::RegisterCommand(Game& game, const std::vector<std::string>& args)
    : game(game), args(args)
{
    if (args.size() != 4)
    {
        throw std::invalid_argument("Usage: register <username> <password> <type>");
    }
    if (args[2].size() < 3)
    {
        throw std::invalid_argument("Password must be at least 3 characters."); 
    }
}

void RegisterCommand::execute()
{
    const std::string& username = args[1];
    const std::string& password = args[2];
    const std::string& type = args[3];

    game.registerUser(username, password, type);
}