#include "Helper.h"
#include <stdlib.h>
#include <iostream>

const char* colors[] = {
	RESET,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	ORANGE,
	BOLDBLACK,
	BOLDRED,
	BOLDGREEN,
	BOLDYELLOW,
	BOLDBLUE,
	BOLDMAGENTA,
	BOLDCYAN,
	BOLDWHITE
};
void clearConsole()
{
	system("cls"); // For Windows
}


void printWelcomeMessage()
{
	std::cout << ORANGE << "===========================================\n";
	std::cout << "	     WELCOME TO        \n";
	std::cout << "		2048!   \n";
	std::cout << "===========================================\n" << RESET;
}

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

int safeReadInt(int min, int max)
{
	int value;
	while (true) {
		std::cin >> value;

		if (!std::cin.fail() && value >= min && value <= max) {
			clearInput();
			return value;
		}

		std::cout << RED << "Invalid input! Try again: " << RESET;
		clearInput();
	}
}

