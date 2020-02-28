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

    void Wait();//等待所有线程任务结束
    
    ~mythreadpool();        
    
    static void work(mythreadpool *,int);
private:
    std::vector<std::thread> work_threads;  //工作线程
    std::queue<std::function<void()>> tasks;//任务队列
    std::mutex tasks_mutex;                 //互斥锁
    std::condition_variable condition;      //条件变量
    bool stop;
};
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

