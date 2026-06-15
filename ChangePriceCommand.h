#pragma once
#include "Command.h"
#include "MarketManager.h"
class ChangePriceCommand : public Command
{
private:
	std::vector<std::string> args;
	MarketManager& marketManager;
	ProductType type;
	double newPrice;
public:
	ChangePriceCommand(MarketManager& manager, const std::vector<std::string>& args);
	void execute() override;
};

