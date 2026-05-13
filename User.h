#pragma once
#include <string>
class User
{
protected:
	std::string username;
	std::string password;
public:
	User(const std::string& username, const std::string& password);
	void logout();
	bool changePassword(std::string oldPassword, std::string newPassword);
	const std::string& profileInfo();
};