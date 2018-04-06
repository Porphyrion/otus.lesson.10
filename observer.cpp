#include "observer.h"

void LogObserver::operator()(){
    Block res;
    while(sharedBlock->txt_q.wait_and_pop(res)){
        obsMetrics.commands = obsMetrics.commands + res.size();
        obsMetrics.blocks++;
        update(res);
    }
    writeMetrics();
};

void LogObserver::update(Block res){
    std::lock_guard<std::mutex> txt_m(sharedBlock->cv_m_txt);
    std::ofstream bulkFile("logFile.txt", std::ios::out | std::ios::app);
    bulkFile<<"bulk: ";
    for(auto i : res){
        bulkFile<<i<<" ";
    }
    bulkFile<<std::endl;
    bulkFile.close();
};

void LogObserver::writeMetrics(){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_c);
    std::cout<<"Log "<<"commands read "<<obsMetrics.commands<<" blocks read "<<obsMetrics.blocks<<std::endl;
};

void CoutObserver::operator()(){
    Block res;
    while(sharedBlock->log_q.wait_and_pop(res)){
        obsMetrics.commands = obsMetrics.commands + res.size();
        obsMetrics.blocks++;
        update(res);
    }
    writeMetrics();
};

void CoutObserver::update(Block res){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_c);
    std::cout<<"bulk: ";
    for(auto i : res)
        std::cout<<i<<" ";
    std::cout<<std::endl;
};

void CoutObserver::writeMetrics(){
    std::lock_guard<std::mutex> cout_m(sharedBlock->cv_m_c);
    std::cout<<"Cout "<<"commands read "<<obsMetrics.commands<<" blocks read "<<obsMetrics.blocks<<std::endl;
};
