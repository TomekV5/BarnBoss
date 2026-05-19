#include <iostream>
#include <fstream>

#include "Game.h"
#include "Helper.h"


int main()
{
	printWelcomeMessage();
	Game game;
	std::cout << "Load or start new game?\n";
	std::cout << "[1] Load\n[2] New\n";
	std::string choice;
	std::cin >> choice;
	if(choice == "1")
	{
		std::cout << "Enter save file name: ";
		std::string filename;
		std::cin >> filename;
		filename = DIRECTORY + filename + TXT_EXTENSION;
		std::ifstream in(filename);
		if(in)
		{
			TaskBoard::getInstance().loadFromFile(in);
			std::cout << "Game loaded successfully!\n";
		}
		else
		{
			std::cout << "Failed to load game. Starting new game.\n";
		}
	}
	else if(choice == "2")
	{
		std::cout << "Starting new game...\n";
	}
	else
	{
		std::cout << "Invalid choice. Starting new game by default.\n";
	}
	/*TaskBoard& board = TaskBoard::getInstance();
	board.addTask(Product(ProductType::Wheat, 10.0, 3, ProductType::Wheat_Seed, 2), 5, 100, 50);
	board.addTask(Product(ProductType::Egg, 5.0, 2, ProductType::Chicken, 1), 10, 50, 30);
	board.showTasks();*/
}