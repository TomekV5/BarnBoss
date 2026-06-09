#pragma once
#include "Command.h"
#include "Market.h"
class OpenMarketCommand : public Command
{
private:
	Market& market;
public:
	OpenMarketCommand(Market& market);
	void execute() override;
};

