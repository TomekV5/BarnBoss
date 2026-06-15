#pragma once
#include<vector>
#include<string>
#include <stdexcept>
#include <iostream>
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};