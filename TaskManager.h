#pragma once
#include "User.h"

class TaskManager : public User
{
private:
    TaskManager(const std::string& username, const std::string& password);

public:
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    // The singleton is created on first registration; username/password are
    // set at that point via setCredentials().
    static TaskManager& getInstance();
    static bool isRegistered();

    // Called once when the TaskManager account is first registered.
    void setCredentials(const std::string& username, const std::string& password);

    std::string profileInfo() const override;

    void showTasks() const;
    bool addTask(const std::string& productName, unsigned quantity,
        double rewardBalance, int rewardScore);
    bool removeTask(unsigned taskId);
    void reset();
};