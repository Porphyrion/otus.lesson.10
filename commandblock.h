#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <utility>
#include <condition_variable>
#include <boost/lexical_cast.hpp>
#include "metrics.h"
#include "threadsafe_queue.h"

enum class Status{
    nothing, start, stop, last_bulk, start_dynamic
};

using Block = std::vector<std::string>;
using timeStampBlock = std::pair<std::string, Block>;

class CommandBlock{
private:
    Block block;
    std::string timeStamp;
    int blockSize;
    bool dynamic;
    Status status;
    std::condition_variable dataCondLog;
    std::condition_variable dataCondTxt;

    void push();

public:
    CommandBlock(int n_);
    CommandBlock(CommandBlock && other) = default;

    void appendCommand(std::string command);
    void setStatus(Status s);

    std::atomic<bool> lastBulk_;
    threadSafeQueuq<Block> log_q{dataCondLog, lastBulk_};
    threadSafeQueuq<timeStampBlock> file_q{dataCondTxt, lastBulk_};
    mutable std::mutex cv_m_l;
    mutable std::mutex cv_m_txt;

    Metrics mainMetrics;
};
