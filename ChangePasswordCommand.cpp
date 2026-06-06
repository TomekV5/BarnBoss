#include "ChangePasswordCommand.h"

ChangePasswordCommand::ChangePasswordCommand(User* user, const std::vector<std::string>& args): user(user), args(args)
{
}

void ChangePasswordCommand::execute()
{
    if (args.size() != 3)
    {
        std::cout << "Usage: changePassword <oldPassword> <newPassword>" << std::endl;
        return;
    }
    if (args[2].size() < 3)
    {
        std::cout << "New password must be at least 3 characters." << std::endl;
        return;
    }
    if (user->changePassword(args[1], args[2]))
        std::cout << "Password changed successfully." << std::endl;
    else
        std::cout << "Incorrect old password." << std::endl;
}
