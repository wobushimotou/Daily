#include <iostream>
#include <vector>
#include <string.h>
/*
    最优调度问题，回溯法
  */
using namespace std;
class BestSchedule{
public:
    int cost[7];    //存储每个任务所需时间
    int way[7];    //记录路径
    int bestway[7];//记录最佳路径
    int machine[3];    //存储每台机器完成任务所需时间
    //得到三台机器中完成时间最长的
    int GetBest() {
        int max = 0;
        for(auto i = 0;i != 3;++i) {
            if(machine[i] > max)
                max = machine[i];
        }
        return max;
    }
    int besttime;   //记录最优调度时间

    void Blacktrack(size_t);

};

void BestSchedule::Blacktrack(size_t n) {
    if(n > 6) {   //到达叶节点，计算最优调度
        if(GetBest() < besttime) {
            besttime = GetBest();
            for(int i = 0;i < 7;++i)
                bestway[i] = way[i];
            return;
        }
    }
    else {
        for(int i = 0;i < 3;++i) {
            way[n] = i;
            machine[i] += cost[n]; 
            if(machine[i] < besttime) {
                Blacktrack(n+1);
            }
            machine[i] -= cost[n];
        }
    }
}
int main()
{
    BestSchedule bs;
    bs.besttime = 9999;
    bzero(bs.machine,3*4);
    bzero(bs.way,7*4);
    bzero(bs.bestway,7*4);

    for(int i = 0;i < 7;++i)
        cin >> bs.cost[i];
    bs.Blacktrack(0);
    cout << bs.besttime << endl;
    for(int i = 0;i < 7;++i)
        cout << bs.bestway[i] << endl;
    return 0;
}

