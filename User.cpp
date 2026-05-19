#include "User.h"

User::User(const std::string& username, const std::string& password):username(username),password(password)
{
}

const std::string& User::profileInfo()
{
	return "User: " + username;
}
