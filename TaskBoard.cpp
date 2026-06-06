#include "TaskBoard.h"
#include <iostream>

TaskBoard& TaskBoard::getInstance()
{
    static TaskBoard instance;
    return instance;
}

void TaskBoard::addTask(const Product& product, unsigned qty,
    double rewardBal, int rewardScore)
{
    tasks.push_back(std::make_unique<Task>(product, qty,
        rewardBal, rewardScore));
}

bool TaskBoard::removeTask(unsigned taskId)
{
    for (auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        if ((*it)->getId() == taskId)
        {
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

void TaskBoard::clearTasks()
{
    tasks.clear();
}

void TaskBoard::showTasks() const
{
    if (tasks.empty())
    {
        std::cout << "No active tasks on the board." << std::endl;
        return;
    }
    std::cout << "=== TASK BOARD ===" << std::endl;
    for (const auto& t : tasks)
    {
        std::cout << t->getId() << ". Deliver "
            << t->getRequiredQuantity() << " "
            << toString(t->getRequiredProduct().getName())
            << " -> Reward: "
            << t->getRewardBalance() << " Balance, "
            << t->getRewardScore() << " Score" << std::endl;
    }
}

Task* TaskBoard::getTaskById(unsigned taskId) const
{
    for (const auto& t : tasks)
        if (t->getId() == taskId)
            return t.get();
    return nullptr;
}

void TaskBoard::saveToFile(std::ostream& out) const
{
    out << tasks.size() << "\n";
    for (const auto& t : tasks)
    {
        out << toInt(t->getRequiredProduct().getName()) << " "
            << t->getRequiredQuantity() << " "
            << t->getRewardBalance() << " "
            << t->getRewardScore() << "\n";
    }
}

void TaskBoard::loadFromFile(std::istream& in)
{
    clearTasks();
    size_t count;
    in >> count;
    for (size_t i = 0; i < count; i++)
    {
        int      typeInt, rewardBalance, rewardScore;
        unsigned qty;
        in >> typeInt >> qty >> rewardBalance >> rewardScore;
        ProductType pt = fromInt(typeInt);
        Product p(pt, 0, 0, ProductType::Undefined, 0);
        addTask(p, qty, rewardBalance, rewardScore);
    }
}