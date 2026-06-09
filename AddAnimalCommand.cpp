#include "AddAnimalCommand.h"

AddAnimalCommand::AddAnimalCommand(Player* player, const std::vector<std::string>& args) :player(player), args(args)
{
	if (args.size() != 2)
	{
		throw std::invalid_argument("Usage: addAnimal <animalId>");
	}
	int animalId = std::stoi(args[1]);
	type = fromInt(animalId);
	if (type != ProductType::Chicken && type != ProductType::Cow)
	{
		throw std::invalid_argument("Invalid animal id. Use 3 (Chicken) or 4 (Cow).");
	}
}

void AddAnimalCommand::execute()
{
	if (player->getFarm().addAnimal(type, player->getBarn())) {
		std::cout << "Animals added successfully!" << std::endl;
	}
}
