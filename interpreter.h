#pragma once

#include <memory>
#include "commandblock.h"
#include "observer.h"

enum class Status{
    nothing, start, stop, last_bulk, start_dynamic
};

class CommandBlock;

class Interpreter{
public:
    Interpreter(int n_): cb{n_}{
        std::cout<<"Inter constr"<<std::endl;
    };
    void readCommand(std::string s);

private:
    CommandBlock cb;
    LogObserver lo{std::make_shared<CommandBlock>(cb)};
    CoutObserver co{std::make_shared<CommandBlock>(cb)};
    long dynamicCounter;

};
