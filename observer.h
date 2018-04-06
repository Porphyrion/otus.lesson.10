#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <condition_variable>
#include <boost/lexical_cast.hpp>
#include "threadsafe_queue.h"
#include "commandblock.h"

class Observer {
public:
    Observer(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_){};
    virtual void update(Block s) = 0;
protected:
    std::shared_ptr<CommandBlock> sharedBlock;
};

class LogObserver : protected Observer{
public:
    LogObserver(std::shared_ptr<CommandBlock> sb_): Observer(sb_){};

    void operator()();
    void update(Block s) override;
};

class CoutObserver : protected Observer{
public:
    CoutObserver(std::shared_ptr<CommandBlock> sb_) : Observer(sb_){};

    void operator()();
    void update(Block s) override;
};
