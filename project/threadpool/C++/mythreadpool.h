#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <memory>
#include <iostream>
class mythreadpool
{
public:
    mythreadpool(size_t n); //构造函数,n表示工作线程数
    //添加任务函数到任务队列
    
    template<class F,class...Args>
    auto Append(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
    
    ~mythreadpool();        
    
    static void work(mythreadpool *,int);
private:
    std::vector<std::thread> work_threads;  //工作线程
    std::queue<std::function<void()>> tasks;//任务队列
    std::mutex tasks_mutex;                 //互斥锁
    std::condition_variable condition;      //条件变量
    bool stop;
};

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

template<class F,class ...Args>
auto mythreadpool::Append(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> {
    
    //获取返回值类型
    using return_type = typename std::result_of<F(Args...)>::type;
    
    //获取任务函数
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f),std::forward<Args>(args)...));
    
    std::future<return_type> res = task->get_future();

    std::unique_lock<std::mutex> lock(this->tasks_mutex);
    this->tasks.emplace( [task](){(*task)();} );
    lock.unlock();

    this->condition.notify_one();
    
    return res;
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

int f(int i) {
    return 10;
}


