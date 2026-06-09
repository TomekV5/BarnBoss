#include "ShowTaskBoardCommand.h"

ShowTaskBoardCommand::ShowTaskBoardCommand(TaskBoard& taskBoard):taskBoard(taskBoard)
{
}

void ShowTaskBoardCommand::execute()
{
	taskBoard.showTasks();
}
