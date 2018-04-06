#include "interpreter.h"

Interpreter::Interpreter(int n_) : cb(std::make_shared<CommandBlock>(n_))
{
    std::cout<<"1 ";
    obsThreads.reserve(4);
    for(auto i = 0; i < 2; ++i)
        co.push_back(std::make_unique<CoutObserver>(cb));
    for(auto i = 0; i < 2; ++i)
        lo.push_back(std::make_unique<LogObserver>(cb));
    std::cout<<"2 ";
    for(auto& i : co)
        obsThreads.emplace_back(std::thread(*i));
    for(auto& i : lo)
        obsThreads.emplace_back(std::thread(*i));
    std::cout<<"3 ";
};

void Interpreter::readCommand(std::string s){
    std::cout<<std::endl<<s<<" ";
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
        cb->appendCommand(s);
    }
};

void Interpreter::lastBulk(){
    cb->setStatus(Status::last_bulk);
};
