#include "OpenMarketCommand.h"

OpenMarketCommand::OpenMarketCommand(Market& market) :market(market)
{
}

void OpenMarketCommand::execute()
{
	market.showCatalog();
}