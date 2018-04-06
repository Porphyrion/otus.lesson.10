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

void CommandBlock::setStatus(Status status_){
    status = status_;
    if(status == Status::start) block.clear();
    else if(status == Status::start_dynamic){
        if(block.size()){
            log_q.push(block);
            txt_q.push(block);
        }
        dynamic = true;
        setStatus(Status::start);
    }
    else if(status == Status::last_bulk){
        lastBulk_.store(false);
        dataCondLog.notify_all();
        dataCondTxt.notify_all();
    }
    else if(status == Status::stop){
        log_q.push(block);
        txt_q.push(block);
        block.clear();
    };
};

threadSafeQueuq<Block>& CommandBlock::getLog(){
    return log_q;
};

threadSafeQueuq<Block>& CommandBlock::getTxt(){
    return txt_q;
};
