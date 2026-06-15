#include "AddTaskCommand.h"


AddTaskCommand::AddTaskCommand(TaskManager& taskManager, const std::vector<std::string>& arguments) :taskManager(taskManager), args(arguments)
{
	if (args.size() != 5)
	{
		throw std::invalid_argument("Usage: addTask <productName> <quantity> <rewardBalance> <rewardScore>");
	}
}

void AddTaskCommand::execute()
{
	unsigned qty = static_cast<unsigned>(std::stoi(args[2]));
	double rewardBalance = std::stod(args[3]);
	int rewardScore = std::stoi(args[4]);

	if (taskManager.addTask(args[1], qty, rewardBalance, rewardScore)) {
		std::cout << "Task added successfully!" << std::endl;
	}
}
