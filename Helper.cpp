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

