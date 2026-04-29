#pragma once
#include <string>
class User
{
protected:
	unsigned id;
	std::string username;
	std::string password;
public:
	void logout();
	bool changePassword(std::string oldPassword, std::string newPassword);
	const std::string& profileInfo();
};