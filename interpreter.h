#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <condition_variable>
#include "commandblock.h"
#include "observer.h"
#include "metrics.h"

class CoutObserver;
class LogObserver;
class CommandBlock;

using  b = std::vector<std::string>;

class Interpreter{
public:
    Interpreter(int n_);
    void readCommand(std::string s);
    void lastBulk();
    std::unique_ptr<Metrics> mainMetrics;

private:
    std::shared_ptr<CommandBlock> cb;
    std::vector<std::unique_ptr<CoutObserver>>  co;
    std::vector<std::unique_ptr<LogObserver>> lo;
    std::vector<std::thread> obsThreads;

    long dynamicCounter;

};
