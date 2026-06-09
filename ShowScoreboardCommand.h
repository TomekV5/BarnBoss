#pragma once
#include "Command.h"
#include "ScoreBoard.h"
class ShowScoreboardCommand : public Command
{
private:
	ScoreBoard& scoreboard;
	const std::vector<Player*> players;
public:
	ShowScoreboardCommand(ScoreBoard& scoreboard, const std::vector<Player*> players);
	void execute() override;
};