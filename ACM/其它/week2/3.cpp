/*
 *  求字符串a被字符集合替换后的最大字典序序列
 *
 * */
#include <iostream>
#include <string>

using namespace std;
int main()
{
    string a;
    string t;
    cin >> a >> t;
    for(auto e:t) {
        for(char &c:a)
            if(c < e) {
                c = e;
                break;
            }
    }
    cout << a << endl;
    return 0;
}

