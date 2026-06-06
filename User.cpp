#include "User.h"

User::User(const std::string& username, const std::string& password)
    : username(username), password(password)
{
}

const std::string& User::getUsername()    const { return username; }
const std::string& User::getPasswordRaw() const { return password; }

bool User::validatePassword(const std::string& pwd) const
{
    return password == pwd;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (password != oldPassword) return false;
    if (newPassword.size() < 3)  return false;
    password = newPassword;
    return true;
}

std::string User::profileInfo() const
{
    return "Username: " + username;
}