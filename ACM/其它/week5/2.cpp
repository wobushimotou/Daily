/*
 *  1-23的数字的集合，求其中两数能组成24的子集的数量
 *
 *
 * */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
int main()
{
    vector<int> v;
    map<int,int> imap;
    int num;
    while(cin >> num)
        v.push_back(num);

    sort(v.begin(),v.end());

    v.erase(unique(v.begin(),v.end()),v.end());
   
    int sum = 0;
    for(auto p = v.begin();p != v.end();++p) {
        imap[*p] = 1;
        if(imap[24-*p]) {
            sum++;
        }
    }

    cout << sum << endl;


    return 0;
}

