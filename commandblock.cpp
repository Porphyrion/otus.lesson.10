#include "commandblock.h"

CommandBlock::CommandBlock(int n_):blockSize(n_), status(Status::nothing) {
    lastBulk_.store(true);
};

void CommandBlock::appendCommand(std::string command){
    if(!dynamic){
        if(block.size() == 0)
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
        block.clear();
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
    else if(status == Status::stop){
        push();
        block.clear();
        timeStamp.clear();
    };
};

void CommandBlock::push(){
    log_q.push(block);
    file_q.push(std::make_pair(timeStamp, block));
    mainMetrics.blocks++;
}
