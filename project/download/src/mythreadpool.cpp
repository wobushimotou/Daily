#include "mythreadpool.h"

mythreadpool::mythreadpool(size_t n) : stop(false){
    for(size_t i = 0;i < n;++i) {
        work_threads.emplace_back(work,this,i);
    }

}
mythreadpool::~mythreadpool() {
    std::unique_lock<std::mutex> lock(this->tasks_mutex);
    this->stop = true;
    lock.unlock();
    //唤醒所有wait状态的线程
    condition.notify_all();
    //等待所有线程执行完
    for(std::thread &e:work_threads) {
        e.join();
    }
}

void mythreadpool::Wait() {
    for(auto &e:work_threads) {
        e.join();
    }
}

void mythreadpool::work(mythreadpool *t,int t_num) {
    while(!t->stop) {
        std::unique_lock<std::mutex> lock(t->tasks_mutex);
        t->condition.wait(lock,
            [t]{return t->stop || !t->tasks.empty();});
    
        //结束时
        if(t->stop && t->tasks.empty())
            return;

        //从任务队列里拿出函数
        std::function<void()> task = t->tasks.front();
        t->tasks.pop();
        lock.unlock();
        //执行函数
        task();
    }
}


