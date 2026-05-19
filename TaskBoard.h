#pragma once
#include <vector>
#include <memory>
#include "Task.h"
class TaskBoard
{
private:
	TaskBoard()=default;
	std::vector<std::unique_ptr<Task>> tasks;
public:
	TaskBoard(const TaskBoard&) = delete;
	TaskBoard operator=(const TaskBoard&) = delete;
	static TaskBoard& getInstance();

    void addTask(const Product& product, unsigned qty, double rewardBal, int rewardScore);
    bool removeTask(int taskId);

    void showTasks() const;
    Task* getTaskById(int taskId) const;

    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};