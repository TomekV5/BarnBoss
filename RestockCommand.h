#pragma once
#include "Command.h"
#include "MarketManager.h"
#include "ProductType.h"
class RestockCommand : public Command
{
private:
	MarketManager& marketManager;
	std::vector<std::string> args;
	ProductType type;
	unsigned quantity;
public:
	RestockCommand(MarketManager& marketManager, const std::vector<std::string>& args);
	void execute() override;
};

