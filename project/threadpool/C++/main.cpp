#include "mythreadpool.h"

#include <ctime>
using namespace std;
int main()
{
    clock_t begin = clock();
    
    char ch; 
    mythreadpool th(10);
    for(int i = 0;i < 10;++i) {
        std::cin >> ch;
        th.Append(std::move(f),i);
    }
    /*
    for(int i = 0;i < 100000;++i) {
        thread t(f,i);
        t.detach();
    }
    */
    clock_t end = clock();
    cout << "time = " << end - begin << endl;
}
