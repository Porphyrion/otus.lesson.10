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

using  Block = std::vector<std::string>;

enum class Status{
    nothing, start, stop, last_bulk, start_dynamic
};

class Observer {
public:
    virtual void update(Status s) = 0;
};

class CommandBlock{
public:
    CommandBlock(int n_, std);
    CommandBlock(CommandBlock const& other);
    threadSafeQueuq<Block> getLog();
    threadSafeQueuq<Block> getTxt();
    void appendCommand(std::string command);
    void subscribe(Observer* obs);
    void setStatus(Status s);
    void notify();

private:

    threadSafeQueuq<Block> log_q;
    threadSafeQueuq<Block> txt_q;
    Block block;
    int blockSize;
    bool dynamic;
};

class LogObserver : protected Observer{
public:
    explicit LogObserver(std::shared_ptr<CommandBlock> sb_);
    void operator()(threadSafeQueuq<block> &q);
    void update(Status s) override;

private:
    std::string bulkBeginTime;
    std::string bulkFileName;
    std::shared_ptr<CommandBlock> sharedBlock;
};

class CoutObserver : protected Observer{
public:
    explicit CoutObserver(std::shared_ptr<CommandBlock> sb_) ;

    void operator()(threadSafeQueuq<block> &q);
    void update(Status s) override;

private:
    std::shared_ptr<CommandBlock> sharedBlock;
};
