/*
 *  小熊吃糖问题
 *  n只小熊，每只有自己的战力和饥饿值，按照战力大小的去糖，每只熊会选择吃最大能填报自己饥饿值的糖并且直到吃的最大的糖会导致撑为止
 *  
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Att{
    int fight;
    int hunger;
};
int main()
{
    vector<int> energys;
    vector<Att> vec;

    int m,n;
    cin >> m >> n;
    int num;
    for(int i = 0;i < n;++i) {
        cin >> num;
        energys.push_back(num);
    }
    for(int i = 0;i < m;++i) {
        int fight,hunger;
        cin >> fight >> hunger;
        vec.push_back({fight,hunger});
    }


    sort(vec.begin(),vec.end(),[](Att a,Att b){return a.fight > b.fight;});
    sort(energys.begin(),energys.end(),[](int a,int b){return a > b;});

    for(auto p = vec.begin();p != vec.end();++p) {
        for(auto q = energys.begin();q != energys.end();++q) {
            if(p->hunger >= *q) {
                p->hunger -= *q;
                *q = 9999;;
            }
        }
    }

    for(auto p = vec.begin();p != vec.end();++p)
        cout << p->hunger << endl;
    return 0;
}

