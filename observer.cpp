#include "observer.h"

void FileObserver::operator()(){
    Block res;
    while(sharedBlock->file_q.wait_and_pop(res)){
        obsMetrics.commands = obsMetrics.commands + res.size();
        ++obsMetrics.blocks;
        update(res);
    }
    writeMetrics();
};

void FileObserver::update(Block res){
    std::lock_guard<std::mutex> txt_m(sharedBlock->cv_m_txt);
    std::ofstream bulkFile("logFile" +id +".txt", std::ios::out | std::ios::app);
    bulkFile<<"bulk: ";
    for(auto i : res){
        bulkFile<<i<<" ";
    }
    bulkFile<<std::endl;
    bulkFile.close();
};

void FileObserver::writeMetrics(){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_txt);
    std::cout<<"File"<<id<<" : commands read "<<obsMetrics.commands<<" blocks read "<<obsMetrics.blocks<<std::endl;
};

void LogObserver::operator()(){
    Block res;
    while(sharedBlock->log_q.wait_and_pop(res)){
        obsMetrics.commands = obsMetrics.commands + res.size();
        ++obsMetrics.blocks;
        update(res);
    }
    writeMetrics();
};

void LogObserver::update(Block res){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_l);
    std::cout<<"bulk: ";
    for(auto i : res)
        std::cout<<i<<" ";
    std::cout<<std::endl;
};

void LogObserver::writeMetrics(){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_l);
    std::cout<<"Log"<<id<<" : commands read "<<obsMetrics.commands<<" blocks read "<<obsMetrics.blocks<<std::endl;
};
