#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include "commandblock.h"
#include "observer.h"
#include "metrics.h"

class CoutObserver;
class LogObserver;
class CommandBlock;

class Interpreter{
public:
    Interpreter(int n_);
    void readCommand(std::string s);
    void lastBulk();
    std::unique_ptr<Metrics> mainMetrics;

private:
    std::shared_ptr<CommandBlock> cb;
    std::vector<std::unique_ptr<FileObserver>>  fo;
    std::vector<std::unique_ptr<LogObserver>> lo;
    std::vector<std::thread> obsThreads;

    long dynamicCounter;
};
