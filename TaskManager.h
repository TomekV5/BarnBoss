#pragma once
#include "User.h"
#include "Product.h"
class TaskManager :public User
{
private:
	TaskManager() = default;
public:
	TaskManager(const TaskManager&) = delete;
	TaskManager operator=(const TaskManager&) = delete;   // Singleton
	static TaskManager& getInstance();
	void showTasks(); /*-показва всички неизпълнени задачи на таблото със задачи*/
	bool addTask(Product requiredProduct, int quantity, double rewardBalance, double rewardScore);/* -добавя нова задача към таблото със задачи*/
	void removeTask(int taskId); /*-премахва задача от таблото със задачи*/
};

