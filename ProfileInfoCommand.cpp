#include "ProfileInfoCommand.h"

ProfileInfoCommand::ProfileInfoCommand(User* user)
    : user(user)
{
}

void ProfileInfoCommand::execute()
{
	std::cout << user->profileInfo() << std::endl;
}
