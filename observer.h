#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <condition_variable>
#include "threadsafe_queue.h"
#include "commandblock.h"
#include "metrics.h"

class Observer {
public:
    Observer(std::shared_ptr<CommandBlock> sb_, int id_) : sharedBlock(sb_),
                                                            obsMetrics(), id(std::to_string(id_)){};
    virtual void writeMetrics() = 0;
protected:
    std::shared_ptr<CommandBlock> sharedBlock;
    Metrics obsMetrics;
    const std::string id;
};

class FileObserver : protected Observer{
public:
    FileObserver(std::shared_ptr<CommandBlock> sb_, int id_): Observer(sb_,id_){};

    void operator()();
    void update(timeStampBlock s);
    void writeMetrics() override;
};

class LogObserver : protected Observer{
public:
    LogObserver(std::shared_ptr<CommandBlock> sb_, int id_) : Observer(sb_, id_){};

    void operator()();
    void update(Block s);
    void writeMetrics() override;
};
