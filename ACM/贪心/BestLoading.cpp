/*
 *  最优装载问题 贪心算法
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class BestLoading{
public:
    vector<int> vec;    //存储货物的重量
    int c;              //船的最大容量
    int GetMax();
};
int BestLoading::GetMax() {
    sort(vec.begin(),vec.end());    //货物重量从小到大依次排序
    int max = 0;
    for(size_t i = 0;i <  vec.size();++i) {
        if(c-vec.at(i) > 0) {
            max += vec.at(i); 
            c -= vec.at(i);
        }
        else
            break;
    }
    return max;
}

int main()
{
    BestLoading bl;
    bl.vec = {3,4,6,2,7,5};
    bl.c = 15;
    cout << bl.GetMax() << endl;
    return 0;
}

