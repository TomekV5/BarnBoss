#include "CheckBalanceCommand.h"

CheckBalanceCommand::CheckBalanceCommand(Player* player) :player(player)
{
}

void CheckBalanceCommand::execute()
{
	std::cout << "Current Balance: " << player->getBalance() << std::endl;
}
