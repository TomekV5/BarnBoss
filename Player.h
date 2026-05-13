#pragma once
#include "User.h"
class Player:public User
{
private:
	static unsigned nextId;
	unsigned id;
	int balance;
	int score;
public:
	Player(const std::string& username, const std::string& password);
};