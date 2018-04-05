#include "interpreter.h"

Interpreter::Interpreter(int n_) : cb(std::make_shared<CommandBlock>(CommandBlock(n_)))
{
    for(auto i = 0; i < 2; ++i)
        co.push_back(CoutObserver(cb));
    for(auto i = 0: i < 2: ++i)
        lo.push_back(LogObserver(cb));

    for(auto i : co)
        obsThreads.push_back(std::thread(i);
    for(auto i : lo)
        obsThreads.push_back(std::thread(i));
};

void Interpreter::readCommand(std::string s){
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
}
