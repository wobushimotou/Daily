#include <iostream>
#include <vector>
#include <algorithm>
/*
    会场活动安排问题　贪心
    */
using namespace std;

struct time{
    int begin;
    int end;
};

bool cmp(vector<struct time>::iterator it,vector<struct time>::iterator its) {
    return it->end > its->end;
}
class VenueArrangement{
public:
    vector<struct time> vec;  //存储每个活动的开始时间和结束时间
    int Mange();
    void Sort() {   //根据每个活动的结束时间排个序
        for(auto p = vec.begin();p != vec.end();++p)
            for(auto q = p+1;q != vec.end();++q) {
                if(p->end > q->end)
                    swap(p,q);
            }
    }
};

int VenueArrangement::Mange() {
    int actNum = 1;
    int endTime = vec.at(0).end;
    for(size_t i = 1;i < vec.size();++i) {
        if(vec.at(i).begin > endTime) { //当前活动开始时间大于上一个活动结束时间
            endTime = vec.at(i).end;
            actNum++;
        }
    }
    return actNum;
}
int main()
{
    int begin,end;
    VenueArrangement va;
    for(int i = 0;i < 5;++i) {
        cin >> begin >> end;
        va.vec.push_back({begin,end});
    }
    va.Sort();
    cout << va.Mange() << endl;
    return 0;
}

