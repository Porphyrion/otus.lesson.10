#include "observer.h"

LogObserver::LogObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_){
    sharedBlock->subscribe(this);

};

CoutObserver::CoutObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_) {
    sharedBlock->subscribe(this);

};

void LogObserver::update(Status s){
    if(s == Status::start){
        bulkBeginTime = boost::lexical_cast<std::string>(time(nullptr));
        bulkFileName = bulkBeginTime;
        bulkFileName.append(".log");
    }
    else if(s == Status::stop){
        std::ofstream bulkFile(bulkFileName, std::ios::out | std::ios::app);
        bulkFile<<"bulk: ";
        for(auto i : sharedBlock->block){
            bulkFile<<i<<" ";
        }
        bulkFile<<std::endl;
        bulkFile.close();
    }
};

void CoutObserver::update(Status s){
    if(s == Status::stop){
        std::cout<<"bulk";
        for(auto i : sharedBlock->block)
            std::cout<<i<<" ";
        std::cout<<std::endl;
    }
};
