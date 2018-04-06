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
    virtual void update(Block s) = 0;
};

class CommandBlock{
private:
    Block block;
    int blockSize;
    bool dynamic;
    Status status;
    std::condition_variable dataCondLog;
    std::condition_variable dataCondTxt;

public:
    CommandBlock(int n_);
    CommandBlock(CommandBlock && other) = default;
    std::atomic_bool loh;
    threadSafeQueuq<Block>& getLog();
    threadSafeQueuq<Block>& getTxt();
    void appendCommand(std::string command);
    //void subscribe(Observer* obs);
    void setStatus(Status s);
    void notify();

    threadSafeQueuq<Block> log_q{dataCondLog, loh};
    threadSafeQueuq<Block> txt_q{dataCondTxt, loh};

};

class LogObserver : protected Observer{
public:
    explicit LogObserver(std::shared_ptr<CommandBlock> sb_);
    LogObserver(LogObserver const& other) = default;
    LogObserver(LogObserver && other) = default;

    void operator()();
    void update(Block s) override;

private:
    //mutable std::mutex cv_m;
    std::string bulkBeginTime;
    std::string bulkFileName;
    std::shared_ptr<CommandBlock> sharedBlock;
};

class CoutObserver : protected Observer{
public:
    explicit CoutObserver(std::shared_ptr<CommandBlock> sb_);
    CoutObserver(CoutObserver && other) = default;
    CoutObserver(CoutObserver const& other) = default;

    void operator()();
    void update(Block s) override;

private:
    //mutable std::mutex cv_m;
    std::shared_ptr<CommandBlock> sharedBlock;
};
