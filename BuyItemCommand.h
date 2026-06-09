#pragma once
#include "Command.h"
#include "Player.h"
#include "Market.h"
class BuyItemCommand : public Command
{
private:
	Player* player;
	ProductType type;
	unsigned quantity;
	Market& market;
	std::vector<std::string> args;
public:
	BuyItemCommand(Player* player,Market& market, const std::vector<std::string>& args);
	void execute() override;
};

