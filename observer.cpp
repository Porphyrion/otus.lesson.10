#include "observer.h"

LogObserver::LogObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_){
};

LogObserver::LogObserver(LogObserver const&other){
        std::unique_lock<std::mutex> lock_other(other.cv_m);
        sharedBlock = other.sharedBlock;
};

CoutObserver::CoutObserver(std::shared_ptr<CommandBlock> sb_) : sharedBlock(sb_) {
};

CoutObserver::CoutObserver(CoutObserver const&other){
    std::unique_lock<std::mutex> lock_other(other.cv_m);
    sharedBlock = other.sharedBlock;
};

void LogObserver::operator()(){
    Block res;
    while(sharedBlock->txt_q.wait_and_pop(res)){
        update(res);
    }
};

void LogObserver::update(Block res){
    std::lock_guard<std::mutex> txt_m(cv_m);
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
    while(sharedBlock->log_q.wait_and_pop(res)){
        update(res);
    }
};

void CoutObserver::update(Block res){
        std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_c);
        std::cout<<"bulk: ";
        for(auto i : res)
            std::cout<<i<<" ";
        std::cout<<std::endl;
};
