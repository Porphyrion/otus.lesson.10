#include "observer.h"

LogObserver::LogObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_){
};

/*LogObserver::LogObserver(LogObserver const&other){
        std::unique_lock<std::mutex> lock_other(other.cv_m);
        sharedBlock = other.sharedBlock;
};*/

CoutObserver::CoutObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_) {
};

/*CoutObserver::CoutObserver(CoutObserver const&other){
    std::unique_lock<std::mutex> lock_other(other.cv_m);
    sharedBlock = other.sharedBlock;
};*/

void LogObserver::operator()(){
    Block res;
    while(sharedBlock->log_q.wait_and_pop(res))
    {
        //std::lock_guard<std::mutex> cout_m(cv_m);
        update(res);
    }
};

void LogObserver::update(Block res){
    std::ofstream bulkFile("logFile.txt", std::ios::out | std::ios::app);
    bulkFile<<"bulk: ";
    for(auto i : res){
        bulkFile<<i<<" ";
    }
    bulkFile<<std::endl;
    bulkFile.close();
};

void CoutObserver::operator()(){
    Block res;
    while(sharedBlock->log_q.wait_and_pop(res))
    {
        //std::lock_guard<std::mutex> cout_m(cv_m);
        update(res);
    }
};

void CoutObserver::update(Block res){
        std::cout<<"bulk: ";
        for(auto i : res)
            std::cout<<i<<" ";
        std::cout<<std::endl;
};
