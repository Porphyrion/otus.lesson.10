#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include<thread>
#include <mutex>
#include <condition_variable>
#include <boost/lexical_cast.hpp>
#include "threadsafe_queue.h"
#include "commandblock.h"

using Block = std::vector<std::string>;

class Observer {
public:
    Observer(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_){};
    virtual void update(Block s) = 0;
protected:
    std::shared_ptr<CommandBlock> sharedBlock;
};

class LogObserver : protected Observer{
public:
    LogObserver(std::shared_ptr<CommandBlock> sb_);
    //LogObserver(LogObserver const& other);
    //LogObserver(LogObserver && other) = default;

    void operator()();
    void update(Block s) override;

private:
    //std::string bulkBeginTime;
    //std::string bulkFileName;
    //std::shared_ptr<CommandBlock> sharedBlock;
};

class CoutObserver : protected Observer{
public:
    CoutObserver(std::shared_ptr<CommandBlock> sb_);
    //CoutObserver(CoutObserver && other) = default;
    //CoutObserver(CoutObserver const& other);

    void operator()();
    void update(Block s) override;

private:
    //std::shared_ptr<CommandBlock> sharedBlock;
};
