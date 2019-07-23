/*
 *  找字符串s的字典序最大的子序列
 *
 * */
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    string t;
    cin >> s;

    for(size_t i = 0;i < s.size();++i) {
        //找出字符串中的最大字母的位置
        int Max = i;
        for(size_t j = i;j < s.size();++j)
            if(s[Max] < s[j])
                Max = j;
        if(Max == s.size()-1) {
            t.push_back(s[Max]);
            break;
        }
        t.push_back(s[Max]);
        s.erase(Max,1);
    }

    cout << "最大子序列为:" << t << endl;
    return 0;
}

