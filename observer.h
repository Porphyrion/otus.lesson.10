#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
    virtual void update(int s) = 0;
};

class CommandBlock{
public:
    CommandBlock(int n_):blockSize(n_), stat(0){
    };
    void appendCommand(std::string command);
    void subscribe(Observer* obs);
    void setStatus(int s);
    void notify();

    std::vector<std::string> block;
private:
    std::vector<Observer*> subs;
    int stat;
    int blockSize;
    bool dynamic;
};

class LogObserver : protected Observer{
public:
    LogObserver(std::shared_ptr<CommandBlock> sb_);
    void update(int s) override;
    /*void operator(){
        this->update();
    };*/
private:
    std::shared_ptr<CommandBlock> sharedBlock;
};

class CoutObserver : protected Observer{
public:
    CoutObserver(std::shared_ptr<CommandBlock> sb_);

    void update(int s) override;
    /*void operator(){
        this->update();
    };*/
private:
    std::shared_ptr<CommandBlock> sharedBlock;
};
