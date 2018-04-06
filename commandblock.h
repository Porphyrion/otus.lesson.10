#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/lexical_cast.hpp>
#include "threadsafe_queue.h"

enum class Status{
    nothing, start, stop, last_bulk, start_dynamic
};

using Block = std::vector<std::string>;

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
    threadSafeQueuq<Block>& getLog();
    threadSafeQueuq<Block>& getTxt();
    void appendCommand(std::string command);
    void setStatus(Status s);
    void notify();

    std::atomic_bool lastBulk_;
    threadSafeQueuq<Block> log_q{dataCondLog, lastBulk_};
    threadSafeQueuq<Block> txt_q{dataCondTxt, lastBulk_};
    mutable std::mutex cv_m_c;

};
