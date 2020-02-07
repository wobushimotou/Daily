#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
#include <mutex>
#include <unistd.h>

using namespace std;
long Count;
mutex Mutex;

void f(long t) {
    int flag = 0;
    int i = 2;
    for(;i < pow(t,0.5);++i) {
        if(t%i == 0)
            flag = 1;
    }
    if(flag) {
        Mutex.lock();
        Count++;
        Mutex.unlock();
    }
}
int main()
{
    for(long i = 0;i != 1000000;++i) {
        thread t(f,i);
        t.detach();
    }
    sleep(1);
    cout << Count << endl;
    return 0;
}

