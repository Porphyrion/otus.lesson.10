#include "observer.h"

void CommandBlock::appendCommand(std::string command){
    if(block.size() == blockSize){
        setStatus(1);
        block.clear();
    }
    block.push_back(command);
}

void CommandBlock::subscribe(Observer * obs){
    subs.push_back(obs);
};

void CommandBlock::setStatus(Status s){
    stat = s;
    if(stat == Status::start) commands.clear();
    else if(stat == Status::start_dynamic){
        if(commands.size())
            setStatus(Stat::stop);
        dynamic = true;
        stat = Status::start;
    }
    else if(status == Status::last_bulk){
        if(!dynamic &&  commands.size() > 0) status = Status::stop;
    }
    notify();
};

void CommandBlock::notify(){
    std::cout<<"hmmm";
    for(auto obs : subs){
        obs->update(stat);
    }
}
