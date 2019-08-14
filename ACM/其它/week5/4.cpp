/*
 *  已知一支股票的股价走势图，至多有两次买入股票，卖出的机会，求所能获得的最大收益
 *
 * */
#include <iostream>
#include <vector>
using namespace std;
int Max(vector<int> &vec,int begin,int end) {
    int mx = 0;
    for(int i = begin;i < end;++i) {
        if(vec[mx] < vec[i])
            mx = i;
    }
    return mx;
}

int Min(vector<int> &vec,int begin,int end) {
    int mn = 0;
    for(int i = begin;i < end;++i) {
        if(vec[mn] > vec[i])
            mn = i;
    }
    return mn;
}

int main()
{

    vector<int> vec;
    int num;
    while(cin >> num)
        vec.push_back(num);

    int result = 0;
    for(int i = 0;i < 2;++i) {
        int Mx = 0,Mn = 0;
        Mx = Max(vec,0,vec.size());
        Mn = Min(vec,0,Mx-1);
        int temp = vec[Mx] - vec[Mn];
        int m = Mx;
        int n = Mn;

        Mn = Min(vec,0,vec.size());
        Mx = Max(vec,Mn+1,vec.size());
        if(temp < vec[Mx]-vec[Mn]) {
            temp = vec[Mx] - vec[Mn];
            vec.erase(vec.begin()+Mx);
            vec.erase(vec.begin()+Mn);
        }
        else {
            vec.erase(vec.begin()+m);
            vec.erase(vec.begin()+n);
        }

        result += temp;
    }
    cout << result << endl;

    return 0;
}

