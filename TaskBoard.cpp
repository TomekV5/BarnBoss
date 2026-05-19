#include "TaskBoard.h"
#include "Task.h"
#include <memory>

TaskBoard& TaskBoard::getInstance()
{
    static TaskBoard instance;
    return instance;
}
void TaskBoard::addTask(const Product& product, unsigned qty, double rewardBal, int rewardScore)
{
	tasks.push_back(std::make_unique<Task>(product, qty, rewardBal, rewardScore));
}

bool TaskBoard::removeTask(int taskId) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)->getId() == taskId) {
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

void TaskBoard::showTasks() const {
    if (tasks.empty()) {
        std::cout << "No active tasks on the board." << std::endl;
        return;
    }

    std::cout << "=== TASK BOARD ===" << std::endl;
    for (const auto& task : tasks) {
        std::cout << task->getId() << ". Deliver "
            << task->getRequiredQuantity() << " "
            << toString(task->getRequiredProduct().getName()) << " -> Reward: "
            << task->getRewardBalance() << " Balance, "
            << task->getRewardScore() << " Score" << std::endl;
    }
}

Task* TaskBoard::getTaskById(int taskId) const {
    for (const auto& task : tasks) {
        if (task->getId() == taskId) {
            return task.get();
        }
    }
    return nullptr;
}

void TaskBoard::saveToFile(std::ostream& out) const
{
}

void TaskBoard::loadFromFile(std::istream& in)
{
}