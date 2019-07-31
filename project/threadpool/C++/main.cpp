#include "mythreadpool.h"

#include <ctime>
using namespace std;
int main()
{
    
    char ch; 
    mythreadpool th(10);

    clock_t begin = clock();

    for(int i = 0;i < 100000;++i) {
        th.Append(std::move(f),i);
    }

    /* for(int i = 0;i < 100000;++i) { */
    /*     thread t(f,i); */
    /*     t.detach(); */
    /* } */

    clock_t end = clock();
    cout << "time = " << end - begin << endl;
}
