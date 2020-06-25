#include <iostream>
#include <string.h>
#include "InitVec.cpp"


//ar[i][j]表示第i个结点的子结点中字符'a'+j结点的位置
int main()
{
    vector<string> vec;
    GetRandVec(vec,20,10);

    int ar[100][26];
    bzero(ar,sizeof(int)*100*26);
    int n;
    int id = 0;

    for(auto &e:vec) {
        n = 0;
        for(size_t i = 0;i != e.size();++i) {
            //得到需处理的字符
            int ch = e[i];
            int ns = ar[n][ch];
            if(ns != 0) {
                n = ns;
            }
            else {
                ar[n][ch] = id++;
            }
        }
    }
    return 0;
}

