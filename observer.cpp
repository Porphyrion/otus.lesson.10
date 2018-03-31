#include "observer.h"

class CommandBlock;

LogObserver::LogObserver(std::shared_ptr<CommandBlock> sb_){
    sharedBlock  = sb_;
    sharedBlock->subscribe(this);
};

CoutObserver::CoutObserver(std::shared_ptr<CommandBlock> sb_){
    sharedBlock  = sb_;
    sharedBlock->subscribe(this);
};

void LogObserver::update(Status s){
        if(s){
            for(auto i : sharedBlock->block)
                std::cout<<i<<" ";
            std::cout<<std::endl;
        }
};

void CoutObserver::update(Status s){
    if(s){
        for(auto i : sharedBlock->block)
            std::cout<<i<<" |";
        std::cout<<std::endl;
    }
};
