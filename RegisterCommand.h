#pragma once
#include "Command.h"
#include "Game.h"

class RegisterCommand : public Command
{
private:
    Game& game;
    std::vector<std::string> args;

public:
    RegisterCommand(Game& game, const std::vector<std::string>& args);
    void execute() override;
};