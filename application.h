#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "interpreter.h"

class Interpreter;

class Application{
public:
    Application(int n_) : interpreter{n_}{
    };
    void run();
private:
    Interpreter interpreter;
};
