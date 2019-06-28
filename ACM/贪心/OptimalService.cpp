#include <iostream>
#include <vector>
/*
    多处服务最优问题　贪心
    */

using namespace std;
struct Custom{
    int serviceTime;//顾客所需服务时间
    int waitTime;   //顾客所需等待时间
    int service_num;//此次服务的服务点
};
class OptimalService{
public:
    vector<Custom> vec; //存储每位顾客信息
    vector<int> service;//存储服务点完成服务所需时间
    int BestService();  //返回顾客的最小平均等待时间
    int GetService() {  //返回最早完成服务的服务点编号
        int Min = 9999;
        size_t i;
        int flag;
        for(i = 0;i < service.size();++i)
            if(service.at(i) < Min) {
                Min = service.at(i);
                flag = i;
            }
            return flag;
    }
};

int OptimalService::BestService() {
    //根据顾客所需服务时间升序排序
    for(auto p = vec.begin();p != vec.end();++p)
        for(auto q = p+1;q != vec.end();++q)
            if(p->serviceTime > q->serviceTime) {
                struct Custom temp;
                temp = *p;
                *p = *q;
                *q = temp;
            }
    
    int customNum = vec.size();
    int num = 0;    //当前处理的顾客
    while(customNum > 0) {
        //得到结束时间最早的服务点编号
        int m = GetService();
        //将顾客放在此服务店进行服务
        service.at(m) += vec.at(num).serviceTime;
        vec.at(num).waitTime = service.at(m);
        vec.at(num).service_num = m;
        
        customNum--;
        num++;
    }
    //返回每位顾客的等待时间的平均值
    int sum = 0;
    for(auto p = vec.begin();p != vec.end();++p)
        sum += p->waitTime;
    return sum/vec.size();
}

int main()
{
    OptimalService os;
    //初始化服务点
    for(int i = 0;i < 2;++i)
        os.service.push_back(0);

    int Time;
    //输入每位顾客所需服务时间
    for(int i = 0;i < 10;++i) {
        cin >> Time;
        os.vec.push_back({Time,0,-1});
    }
    cout << os.BestService() << endl;
    return 0;
}

