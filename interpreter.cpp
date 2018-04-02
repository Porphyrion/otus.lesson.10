#include "interpreter.h"

Interpreter::Interpreter(int n_) : cb(std::make_shared<CommandBlock>(CommandBlock(n_))),
co(cb), lo(cb)
{

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
