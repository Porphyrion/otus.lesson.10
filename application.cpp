#include "application.h"

void Application::run(){
    std::string line;
    while(std::getline(std::cin, line)){
        interpreter.readCommand(line);
    }
};
