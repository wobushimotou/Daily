/*
 *  会话列表问题，按照时间顺序输入一组会话id,输出最后显示的会话列表
 *
 * */
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

int main()
{
    deque<int> ique;
    int n;
    int num;
    cin >> n;
    for(int j = 0;j < n;++j) {
        cin >> num;
        deque<int>::iterator it = find(ique.begin(),ique.end(),num);
        if(it != ique.end()) {
            ique.erase(it);
        }
        ique.push_front(num);
    }
    for(auto e:ique) {
        cout << e << " ";
    }

    return 0;
}

