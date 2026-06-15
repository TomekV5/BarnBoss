#pragma once
#include "Command.h"
#include "Player.h"
class AdvanceCycleCommand : public Command
{
private:
    Player* player;
public:
    explicit AdvanceCycleCommand(Player* player);
    void execute() override;
};
