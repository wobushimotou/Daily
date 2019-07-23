/*
 *  求字符串a中字符串集合b所有字符串出现的种数
 *
 *
 * */
#include <iostream>
#include <string>
#include <map>

using namespace std;
int main()
{
    string a,b;
    cin >> a >> b;
    map<string,int> imap;
    

    if(a.size() < b.size()) {
        cout << "b.length error" << endl;
        return 0;
    }

    for(size_t i = 0;i <= a.size()-b.size();++i) {
        string temp = a.substr(i,b.size());
        size_t j = i;
        for(;j < i+b.size();++j) {
            if(b[j-i] == '?' || temp[j] == b[j-i]) {
                continue;
            }
            else
                break;
        }
        if(j == i+b.size())
            imap[temp]++;
    }
    cout << "能匹配的字符串种数为:" << imap.size() << endl;
    return 0;
}

