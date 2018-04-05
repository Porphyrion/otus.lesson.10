#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class threadSafeQueuq{
private:
    mutable std::mutex mut;
    std::queue<T> dataQueue;
    std::condition_variable dataCond;
    std::atomic<bool>& stat;

public:

    threadSafeQueuq(){

     };
    threadSafeQueuq(threadSafeQueuq const& other){
        std::lock_guard<std::mutex> lk(other.mut);
        dataQueue =  other.dataQueue;
    };

    void push(T new_value){
        std::lock_guard<std::mutex> lk(mut);
        dataQueue.push(new_value);
        dataCond.notify_one();
    };

    bool wait_and_pop(T& value){
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this]{return !dataQueue.empty() ;});// || !stat;});
        value = dataQueue.front();
        dataQueue.pop();
        return true;
    };

    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this]{return !dataQueue.empty() ;});
        auto res = std::make_shared<T>(dataQueue.front());
        dataQueue.pop();
        return res;
    };

    bool try_pop(T &value){
        std::lock_guard<std::mutex> lk(mut);
        if(dataQueue.empty()) return false;
        value = dataQueue.front();
        dataQueue.pop();
        return true;
    };

    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lk(mut);
        if(dataQueue.empty()) return false;
        auto res = std::make_shared<T>(dataQueue.front());
        dataQueue.pop();
        return res;
    };

    bool empty() const{
        std::lock_guard<std::mutex> lk(mut);
        return dataQueue.empty();
    };
};
