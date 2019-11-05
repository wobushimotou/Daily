#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{
    deque<int> head;
    head.emplace(head.begin(),99);
    head.emplace(head.begin(),88);
    head.emplace(head.begin(),77);

    sort(head.begin(),head.end(),[](int &a,int &b){return a < b;});
    for(auto p = head.begin();p != head.end();++p)
        cout << *p << endl;

    return 0;
}

