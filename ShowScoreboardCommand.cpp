#include "ShowScoreboardCommand.h"

ShowScoreboardCommand::ShowScoreboardCommand(ScoreBoard& scoreboard, const std::vector<Player*> players):
	scoreboard(scoreboard),
	players(players)	
{
}

void ShowScoreboardCommand::execute()
{
	scoreboard.showScoreboard(players);
}
