#include <atomic>

class Metrics{
    std::atomic<int> blocks;
    std::atomic<int> commands;
}
