#include "ScoreBoard.h"
ScoreBoard& ScoreBoard::getInstance()
{
	static ScoreBoard instance;
	return instance;
}