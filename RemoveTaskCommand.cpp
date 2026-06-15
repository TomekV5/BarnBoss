#include "RemoveTaskCommand.h"

RemoveTaskCommand::RemoveTaskCommand(TaskManager& taskManager, const std::vector<std::string>& args)
	: taskManager(taskManager), args(args)
{
	if (args.size() != 2)
	{
		throw std::invalid_argument("Usage: removeTask <taskId>");
	}
}

void RemoveTaskCommand::execute()
{
	unsigned taskId = static_cast<unsigned>(std::stoi(args[1]));
	if (taskManager.removeTask(taskId))
		std::cout << "Task removed successfully." << std::endl;
	else
		std::cout << "Task not found." << std::endl;
}