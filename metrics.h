#pragma once

#include <atomic>

class Metrics{
public:
    Metrics():blocks(0), commands(0), lines(0){};
    int blocks;
    int commands;
    int lines;
};
