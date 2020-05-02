#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;
int GetNum(int k,int m,int n) {//得到I的[m:n]范围内的后k位数字
    int I = 1231;
    string num;
    stringstream os;
    os << I;
    os >> num;
    int value = 0;
    m--,n--;
    for(int i = n+1-k;i <= n;++i)
        value = value*10 + num[i]-'0';

    return value;
}
void f(vector<int> &vec) {
    
}
int main()
{
    vector<int> vec;
    thread t(f,std::ref(vec));
    t.join();
    return 0;
}

