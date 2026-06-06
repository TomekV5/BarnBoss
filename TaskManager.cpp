#include "TaskManager.h"
#include "TaskBoard.h"
#include "ProductType.h"
#include <iostream>

// Private constructor – dummy credentials; real ones set via setCredentials
TaskManager::TaskManager(const std::string& username, const std::string& password)
    : User(username, password)
{
}

static bool taskManagerRegistered = false;

TaskManager& TaskManager::getInstance()
{
    static TaskManager instance("__tm__", "__tm__");
    return instance;
}

bool TaskManager::isRegistered()
{
    return taskManagerRegistered;
}

void TaskManager::setCredentials(const std::string& uname, const std::string& pwd)
{
    username = uname;
    password = pwd;
    taskManagerRegistered = true;
}

std::string TaskManager::profileInfo() const
{
    return "Username: " + username + "\nType: TaskManager";
}

void TaskManager::showTasks() const
{
    TaskBoard::getInstance().showTasks();
}

bool TaskManager::addTask(const std::string& productName, unsigned quantity,
    double rewardBalance, int rewardScore)
{
    // Convert name string to ProductType
    ProductType pt = ProductType::Undefined;
    for (int i = 1; i <= 8; i++)
    {
        if (toString(fromInt(i)) == productName)
        {
            pt = fromInt(i);
            break;
        }
    }
    if (pt == ProductType::Undefined)
    {
        std::cout << "Unknown product: " << productName << std::endl;
        return false;
    }
    // Build a minimal Product to satisfy TaskBoard::addTask signature
    Product p(pt, 0, 0, ProductType::Undefined, 0);
    TaskBoard::getInstance().addTask(p, quantity,
        rewardBalance,
        rewardScore);
    return true;
}

bool TaskManager::removeTask(unsigned taskId)
{
    return TaskBoard::getInstance().removeTask(taskId);
}