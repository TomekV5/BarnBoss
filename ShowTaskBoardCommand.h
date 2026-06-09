#pragma once
#include "Command.h"
#include "TaskBoard.h"
class ShowTaskBoardCommand :public Command
{
private:
	TaskBoard& taskBoard;
public:
	ShowTaskBoardCommand(TaskBoard& taskBoard);
	void execute() override;
};

