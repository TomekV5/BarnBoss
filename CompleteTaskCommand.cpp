#include "CompleteTaskCommand.h"

CompleteTaskCommand::CompleteTaskCommand(Player* player, TaskBoard& taskBoard, const std::vector<std::string>& args):
	player(player),
	taskBoard(taskBoard),
	args(args)
{
	if (args.size() != 2)
	{
		throw std::invalid_argument("Usage: completeTask <taskId>");
	}
	taskId = std::stoi(args[1]);

	task = taskBoard.getTaskById(taskId);
	if (!task)
	{
		throw std::invalid_argument("Task not found.");
	}

	required = task->getRequiredProduct().getName();
	quantity = task->getRequiredQuantity();

	if (!player->getBarn().hasProduct(required, quantity))
	{
		std::cout << "Not enough " << toString(required) << " in barn. Need "
			<< quantity << "." << std::endl;
		throw std::invalid_argument("Not enough products in barn.");
	}
}

void CompleteTaskCommand::execute()
{
	player->getBarn().removeProduct(required, quantity);
	player->addBalance(task->getRewardBalance());
	player->addScore(task->getRewardScore());
	taskBoard.removeTask(taskId);
	player->getFarm().advanceCycles();

	std::cout << "Task completed! Reward: +" << task->getRewardBalance()
		<< " Balance, +" << task->getRewardScore() << " Score." << std::endl;
}
