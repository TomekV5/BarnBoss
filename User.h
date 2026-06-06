#pragma once
#include <string>

class User
{
protected:
    std::string username;
    std::string password;

public:
    User(const std::string& username, const std::string& password);
    virtual ~User() = default;

    const std::string& getUsername()    const;
    const std::string& getPasswordRaw() const;   // needed for save/load only

    bool validatePassword(const std::string& pwd) const;
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);

    virtual std::string profileInfo() const;
};