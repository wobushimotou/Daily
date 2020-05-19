#include <iostream>
#include <unistd.h>
typedef void (*timer_func_t)();

class Timer {

    //清空timer

    void clear() {
        fun = NULL;
    }

    //执行timer  

    void run() {
        fun();
    }

        // 在固定时间触发

    void on(const char *datetime, timer_func_t  func) {
        
    }

        // 在N秒后触发

    void after(const int seconds,   timer_func_t func) {
        sleep(seconds);
        func();
    }

        // 每隔N秒触发

    void every(const int interval,  timer_func_t func) {
        while(true) {
            sleep(interval);
            func();
        }
    }

    timer_func_t fun;
};

