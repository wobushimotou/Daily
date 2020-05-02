#include <iostream>

using namespace std;

long to_num(string s) {
    long sum = 0;
    for(int i = 0;i != s.size();++i) {
        sum = sum*10+ s[i]-'0';
    }
    return sum;
}

int main()
{
    string s;
    getline(cin,s);
    cout << to_num(s) << endl;
    return 0;
}

