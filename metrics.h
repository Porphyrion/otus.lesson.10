#include <atomic>

class Metrics{
    std::atomic<int> blocks{0};
    std::atomic<int> commands{0};
    std::atomic<int> lines{0};
};
