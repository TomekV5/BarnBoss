#include "Player.h"
unsigned Player::nextId = 0;

Player::Player(const std::string& username, const std::string& password) :User(username, password)
{
	id = nextId++;
	balance = 100;
	score = 0;
}