#pragma once
#include "Command.h"
#include "TaskManager.h"
class RemoveTaskCommand : public Command
{
private:
	TaskManager& taskManager;
	std::vector<std::string> args;
public:
	RemoveTaskCommand(TaskManager& taskManager, const std::vector<std::string>& args);
	void execute() override;
};

