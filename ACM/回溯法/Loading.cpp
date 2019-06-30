/*
 *  装载问题 回溯法
 *
 *
 *
 * */
#include <iostream>
#include <vector>

using namespace std;
class Loading{
public:
    int c1,c2;  //两艘轮船的载重量
    vector<int> w;  //存储货物的重量
    int best;       //记录第一艘轮船最优装载量
    int c;          //记录第一艘轮船当前解
    int x[50];      //记录当前路径
    int bestx[50];  //记录最优路径
    void GetBest(size_t);
};
void Loading::GetBest(size_t n) {
    if(n == w.size()) {//到达叶结点，记录最优解
        if(c > best) {
            best = c;
            for(int i = 0;i < n;++i)
                bestx[i] = x[i];
        }
    }
    else {
        if(c + w[n] <= c1) {  //可行
            c += w[n];
            x[n] = 1;
            GetBest(n+1);    
            c -= w[n];
            x[n] = 0;
        }
        x[n] = 0;
        GetBest(n+1);
    }
}
int main()
{
    Loading ld;
    ld.c1 = 15,ld.c2 = 15;
    ld.w = {2,2,3,4,5,6};
    ld.best = 0;
    ld.c = 0;
    ld.GetBest(0);
    cout << "放在第一艘船上的货物为";
    for(size_t i = 0;i < ld.w.size();++i) {
        if(ld.bestx[i])
            cout << ld.w.at(i) << " ";

    }
    return 0;
}

