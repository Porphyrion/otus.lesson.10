#pragma once

#include <memory>
#include "observer.h"

class CoutObserver;
class LogObserver;
class CommandBlock;

class Interpreter{
public:
    Interpreter(int n_);
    void readCommand(std::string s);
    void lastBulk();

private:
    std::shared_ptr<CommandBlock> cb;
    LogObserver lo;
    CoutObserver co;
    long dynamicCounter;
};
