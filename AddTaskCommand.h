#pragma once
#include "Command.h"
#include "TaskManager.h"
class AddTaskCommand : public Command
{
private:
	TaskManager& taskManager;
	std::vector<std::string> args;
public:
	AddTaskCommand(TaskManager& taskManager, const std::vector<std::string>& arguments);
	void execute() override;
};

