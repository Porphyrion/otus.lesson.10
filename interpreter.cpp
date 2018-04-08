#include "interpreter.h"

Interpreter::Interpreter(int n_) : cb(std::make_shared<CommandBlock>(n_)), logThreads(1), fileThreads(2)
{
    mainMetrics = std::unique_ptr<Metrics>();
    obsThreads.reserve(4);
    for(auto i = 0; i < fileThreads; ++i)
        fo.push_back(std::make_unique<FileObserver>(new FileObserver(cb, i)));
    for(auto i = 0; i < logThreads; ++i)
        lo.push_back(std::make_unique<LogObserver>(new LogObserver(cb, i)));
    for(auto& i : fo)
        obsThreads.emplace_back(std::thread(*i));
    for(auto& i : lo)
        obsThreads.emplace_back(std::thread(*i));
};

Interpreter::Interpreter(int n_, int lt_, int tt_) : cb(std::make_shared<CommandBlock>(n_)), logThreads(lt_), fileThreads(tt_)
{
    mainMetrics = std::unique_ptr<Metrics>();
    obsThreads.reserve(4);
    for(auto i = 0; i < fileThreads; ++i)
        fo.push_back(std::make_unique<FileObserver>(cb, i));
    for(auto i = 0; i < logThreads; ++i)
        lo.push_back(std::make_unique<LogObserver>(cb, i));
    for(auto& i : fo)
        obsThreads.emplace_back(std::thread(*i));
    for(auto& i : lo)
        obsThreads.emplace_back(std::thread(*i));
};

void Interpreter::readCommand(std::string s){
    cb->mainMetrics.lines++;
    if(s == "{"){
        if(!dynamicCounter)
            cb->setStatus(Status::start_dynamic);
        dynamicCounter++;
    }
    else if(s == "}"){
        dynamicCounter--;
        if(!dynamicCounter)
            cb->setStatus(Status::stop);
    }
    else{
        cb->mainMetrics.commands++;
        cb->appendCommand(s);
    }
};

void Interpreter::lastBulk(){
    cb->setStatus(Status::last_bulk);
    for(auto& i : obsThreads){
        i.join();
    }
    std::cout<<"Main thread: line "<<cb->mainMetrics.lines<<" commands "<<cb->mainMetrics.commands
        <<" blocks "<<cb->mainMetrics.blocks<<std::endl;

};
