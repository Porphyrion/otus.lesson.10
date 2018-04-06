#include "interpreter.h"

Interpreter::Interpreter(int n_) : cb(std::make_shared<CommandBlock>(n_))
{
    mainMetrics = std::unique_ptr<Metrics>();
    obsThreads.reserve(4);
    for(auto i = 0; i < 2; ++i)
        co.push_back(std::make_unique<CoutObserver>(cb));
    for(auto i = 0; i < 2; ++i)
        lo.push_back(std::make_unique<LogObserver>(cb));
    for(auto& i : co)
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
