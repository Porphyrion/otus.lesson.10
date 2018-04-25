#include "commandblock.h"

CommandBlock::CommandBlock(int n_):blockSize(n_), status(Status::nothing) {
    lastBulk_.store(true);
};

void CommandBlock::appendCommand(std::string command){
    if(!dynamic){
        if(!block.size())
            setStatus(Status::start);
        block.push_back(command);
        if(block.size() == blockSize)
            setStatus(Status::stop);
    } else {
        block.push_back(command);
    }
};

void CommandBlock::setStatus(Status newStatus){
    status = newStatus;
    if(status == Status::start){
        timeStamp = boost::lexical_cast<std::string>(time(nullptr));
    }
    else if(status == Status::start_dynamic){
        if(block.size()) push();
        dynamic = true;
        setStatus(Status::start);
    }
    else if(status == Status::last_bulk){
        if(block.size())  push();
        lastBulk_.store(false);
        dataCondLog.notify_all();
        dataCondTxt.notify_all();
    }
    else if(status == Status::last_bulk){
        lastBulk_.store(false);
        dataCondLog.notify_all();
        dataCondTxt.notify_all();
    }
    else if(status == Status::stop){
        if(dynamic) dynamic = false;
        push();
    };
};

void CommandBlock::push(){
    log_q.push(block);
    file_q.push(std::make_pair(timeStamp, block));
    block.clear();
    timeStamp.clear();
    mainMetrics.blocks++;
}
