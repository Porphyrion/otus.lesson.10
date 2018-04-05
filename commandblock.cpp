#include "observer.h"

CommandBlock::CommandBlock(int n_):blockSize(n_), status(Status::nothing), {
};

CommandBlock::CommandBlock(CommandBlock const& other){
    std::lock_guard<std::mutex> lk(other.dm);
    blockSize = other.blockSize;
}

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

void CommandBlock::subscribe(Observer * obs){
    subs.push_back(obs);
};

void CommandBlock::setStatus(Status s){
    status = s;
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
        if(!dynamic &&  block.size() > 0) status = Status::stop;
    }
    else if(status == Status::stop){
        log_q.push(block);
        txt_q.push(block);
        block.clear();
    };
    //notify();
};

void CommandBlock::notify(){
    for(auto i : subs){
        i->update(status);
    }
    if(status == Status::stop) {
        block.clear();
        if(dynamic) dynamic = false;
    }
};

threadSafeQueuq<Block> getLog(){
    return log_q;
};

threadSafeQueuq<Block> getTxt(){
    return txt_q;
};
