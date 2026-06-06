#pragma once
#include<vector>
#include<string>
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};