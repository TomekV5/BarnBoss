#include "ScoreBoard.h"
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

ScoreBoard& ScoreBoard::getInstance()
{
    static ScoreBoard instance;
    return instance;
}

void ScoreBoard::showScoreboard(const std::vector<Player*>& players) const
{
    if (players.empty())
    {
        std::cout << "No players registered yet." << std::endl;
        return;
    }

   std::vector<Player*> sorted = players;
    std::sort(sorted.begin(), sorted.end(), [](const Player* a, const Player* b)
        {
            if (a->getScore() != b->getScore())
                return a->getScore() > b->getScore();
            if (a->getBalance() != b->getBalance())
                return a->getBalance() > b->getBalance();
            return a->getId() < b->getId();
        });

    std::cout << "=== SCOREBOARD ===" << std::endl;
    int rank = 1;
    for (const Player* p : sorted)
    {
        std::cout << rank++ << ". "
            << std::left << std::setw(12) << p->getUsername()
            << "| Score: " << p->getScore()
            << " | Balance: " << std::fixed << std::setprecision(2) << p->getBalance()
            << std::endl;
    }
}