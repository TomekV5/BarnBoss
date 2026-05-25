#include "Player.h"
unsigned Player::nextId = 1;

Player::Player(const std::string& username, const std::string& password) :User(username, password)
{
	id = nextId++;
	balance = 100;
	score = 0;
}

const std::string& Player::profileInfo()
{
	return "Player: " + username + "\nID: " + std::to_string(id) + "\nBalance: " + std::to_string(balance) + "\nScore: " + std::to_string(score);
}

bool Player::setBalance(int newBalance)
{
	if (newBalance < 0)
		return false;
	balance = newBalance;
	return true;
}

bool Player::setScore(int newScore)
{
	if(newScore < 0)
		return false;
	score = newScore;
	return true;
}

double Player::getBalance() const
{
	return balance;
}

Barn& Player::getBarn()
{
	return barn;
}
