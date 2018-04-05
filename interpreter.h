#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <condition_variable>
#include "observer.h"

class CoutObserver;
class LogObserver;
class CommandBlock;

using  b = std::vector<std::string>;

class Interpreter{
public:
    Interpreter(int n_);
    void readCommand(std::string s);
    void lastBulk();

private:
    std::shared_ptr<CommandBlock> cb;
    std::vector<CoutObserver>  co;
    std::vector<LogObserver> lo;
    std::<thread> obsThreads;
    std::condition_variable dataCondLog;
    std::condition_variable dataCondTxt;

    long dynamicCounter;

};
