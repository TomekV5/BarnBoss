#include "AddAnimalCommand.h"

AddAnimalCommand::AddAnimalCommand(Player* player, const std::vector<std::string>& args) :player(player), args(args)
{
	if (args.size() != 2)
	{
		throw std::invalid_argument("Usage: addAnimal <animalName>");
	}
	type = fromString(args[1]);
	if (type != ProductType::Chicken && type != ProductType::Cow)
	{
		throw std::invalid_argument("Invalid animal name. Use 'Chicken' or 'Cow'.");
	}
}

void AddAnimalCommand::execute()
{
	if (player->getFarm().addAnimal(type, player->getBarn())) {
		std::cout << "Animals added successfully!" << std::endl;
	}
}
