#pragma once
#include "User.h"
#include "Barn.h"
#include "Farm.h"
class Player:public User
{
private:
	static unsigned nextId;
	unsigned id;
	int balance;
	int score;
	Barn barn;
	Farm farm;
public:
	Player(const std::string& username, const std::string& password);
	const std::string& profileInfo() override;
	bool setBalance(int newBalance);
	bool setScore(int newScore);
	const Barn& getBarn() const;
};