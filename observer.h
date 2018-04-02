#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

enum class Status{
    nothing, start, stop, last_bulk, start_dynamic
};

class Observer {
public:
    virtual void update(Status s) = 0;
};

class CommandBlock{
public:
    CommandBlock(int n_):blockSize(n_), status(Status::nothing){
    };
    void appendCommand(std::string command);
    void subscribe(Observer* obs);
    void setStatus(Status s);
    void notify();

    std::vector<std::string> block;
private:

    std::vector<Observer*> subs;
    Status status;
    int blockSize;
    bool dynamic;
};

class LogObserver : protected Observer{
public:
    explicit LogObserver(std::shared_ptr<CommandBlock> sb_);
    void update(Status s) override;

private:
    std::string bulkBeginTime;
    std::string bulkFileName;
    std::shared_ptr<CommandBlock> sharedBlock;
};

class CoutObserver : protected Observer{
public:
    explicit CoutObserver(std::shared_ptr<CommandBlock> sb_) ;

    void update(Status s) override;

private:
    std::shared_ptr<CommandBlock> sharedBlock;
};
