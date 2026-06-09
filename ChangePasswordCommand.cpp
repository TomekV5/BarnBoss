#include "ChangePasswordCommand.h"

ChangePasswordCommand::ChangePasswordCommand(User* user, const std::vector<std::string>& args): user(user), args(args)
{
    if (args.size() != 3)
    {
        throw std::invalid_argument("Usage: changePassword <oldPassword> <newPassword>");
    }
    if (args[2].size() < 3)
    {
        throw std::invalid_argument("New password must be at least 3 characters.");
    }
}

void ChangePasswordCommand::execute()
{
    if (user->changePassword(args[1], args[2]))
        std::cout << "Password changed successfully." << std::endl;
    else
        std::cout << "Incorrect old password." << std::endl;
}
