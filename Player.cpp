#include "Player.h"
#include <sstream>
#include <iomanip>

unsigned Player::nextId = 1;

Player::Player(const std::string& username, const std::string& password)
    : User(username, password), id(nextId++), balance(100.0), score(0)
{
}

unsigned Player::getId()      const { return id; }
double   Player::getBalance() const { return balance; }
int      Player::getScore()   const { return score; }
Barn& Player::getBarn() { return barn; }
Farm& Player::getFarm() { return farm; }

bool Player::setBalance(double newBalance)
{
    if (newBalance < 0) return false;
    balance = newBalance;
    return true;
}

bool Player::setScore(int newScore)
{
    if (newScore < 0) return false;
    score = newScore;
    return true;
}

void Player::addBalance(double amount) { balance += amount; }
void Player::addScore(int amount) { score += amount; }

std::string Player::profileInfo() const
{
    std::ostringstream oss;
    oss << "Username: " << username << "\n"
        << "Type: Player\n"
        << "Balance: " << std::fixed << std::setprecision(2) << balance << "\n"
        << "Score: " << score;
    return oss.str();
}

void Player::saveToFile(std::ostream& out) const
{
    out << "Player " << username << " " << password << " "
        << balance << " " << score << "\n";
    barn.saveToFile(out);
    farm.saveToFile(out);
}

void Player::loadFromFile(std::istream& in)
{
    in >> balance >> score;
    barn.loadFromFile(in);
    farm.loadFromFile(in);
}