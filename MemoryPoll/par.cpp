#include <iostream>
#include <memory>
#include <vector>
using namespace std;
int main()
{
    unique_ptr<char[]> area(new char[10]);
    void *p = (void *)(area.get()+5);
    
    long t = (char *)p - (char *)(area.get());
    cout << t << endl;
    return 0;
}

