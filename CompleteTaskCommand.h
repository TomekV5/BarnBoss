#pragma once
#include "Command.h"
#include "Player.h"
#include "TaskBoard.h"
class CompleteTaskCommand :public Command
{
private:
	Player* player;
	TaskBoard& taskBoard;
	const std::vector<std::string>& args;
	Task* task;
	unsigned quantity;
	int taskId;
	ProductType required;
public:
	CompleteTaskCommand(Player* player, TaskBoard& taskBoard, const std::vector<std::string>& args);
	void execute() override;
};

