#include "interpreter.h"

void Interpreter::readCommand(std::string s){
    if(s == "{"){
        if(!dynamic_counter)
            cb->setStatus(Status::start_dynamic);
        dynamic_counter++;
    }
    else if(s == "}"){
        dynamic_counter--;
        if(!dynamic_counter)
            cb->setStatus(Status::stop);
    }
    else{
        cb.appendCommand(s);
    }



};
