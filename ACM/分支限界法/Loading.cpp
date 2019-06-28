#include <iostream>
#include <deque>
#include <vector>
/*
    装载问题　队列式分支限界法
 */
using namespace std;
class Loading{
public:
    deque<int> Que; //储存结点信息
    int depth;      //标识层数
    int ew;         //当前节点的重量
    int bestw;      //最优重量
    int c;          //载重点最大载重量
    vector<int> w;     //每个货物的重量
    void EnQueue(int wt,size_t i); //将结点添加到Que中 wt表示此结点载重量,i为层数
    int Load();
};
void Loading::EnQueue(int wt,size_t i) {
    if(i == w.size()){//到达叶子结点,计算最优解
        if(wt > bestw)
            bestw = wt;
    }
    else 
        //将此结点加入队列
        Que.push_back(wt);
}

int Loading::Load() {
    ew = 0;
    bestw = 0;
    depth = 0;
    Que.push_back(-1);
    while(true) {
        if(ew + w[depth] <= c) {    //左子树成立
            //将左子树添加进队列
            EnQueue(ew+w[depth],depth);
        }
        //将右子树加入队列
        EnQueue(ew,depth); 
        ew = *(Que.begin());
        //取下一结点为扩展结点并将重量保存在ew
        if(ew == -1) {  //同层结束
            if(Que.empty())
                return bestw;
            Que.push_back(-1);
            Que.pop_front();
            ++depth;
        }
        else {
            if(*(Que.begin()+1) == -1) {
                if(Que.size() == 2)
                    return bestw;
                Que.push_back(-1);
                Que.pop_front();    
                ++depth;
            }
            Que.pop_front();
        }
        ew = *(Que.begin());
    }
}
int main()
{
    Loading l;
    cout << "输入最大装载量:";
    cin >> l.c;
    cout << "输入货物的重量:";
    int n;
    for(int i = 0;i < 3;++i) {
        cin >> n;
        l.w.push_back(n);
    }
    cout << l.Load() << endl;
    
    return 0;
}

