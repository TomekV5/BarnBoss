#pragma once
#include <vector>
#include <iostream>

// Forward declaration – ScoreBoard only needs pointers/refs to Player
class Player;

class ScoreBoard
{
private:
    ScoreBoard() = default;
public:
    ScoreBoard(const ScoreBoard&) = delete;
    ScoreBoard& operator=(const ScoreBoard&) = delete;

    static ScoreBoard& getInstance();

    // Pass the full list of players; showScoreboard sorts a copy internally.
    void showScoreboard(const std::vector<Player*>& players) const;
};