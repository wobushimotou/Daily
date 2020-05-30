#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Day{
    Day(int d,long m):day(d),money(m) {  }
    int day;
    long money;
};

int main()
{
    int n;
    cin >> n;

    int day,sec,money;

    vector<pair<int,Day>> vec;
    for(int i = 0;i != n;++i) {
        cin >> day >> sec >> money;

        size_t s = vec.size();
        for(size_t n = 0; n != s;++n) {
            int _abs = sec - vec[n].first;
            if(_abs >= 0 && _abs <= 7200) {
                if(day == vec[n].second.day)
                    vec[n].second.money = money;
                else {
                    vec[n].second.day = day;
                    vec[n].second.money += money;
                }
            }
            if(_abs > 7200)
                break;

        }
        vec.push_back(make_pair(sec,Day(day,money)));
    }

    for(auto &e:vec)
        cout << e.first << " " << e.second.money << endl;
    

    long Max = 0;
    int Maxi = -1;
    
    for(size_t i = 0;i != vec.size();++i) {
        if(Max < vec[i].second.money) {
            Max = vec[i].second.money;
            Maxi = i;
        }
        if(Max == vec[i].second.money) {
            if(vec[Maxi].first > vec[i].first) {
                Max = vec[i].second.money;
                Maxi = i;
            }

        }
    }

    cout << vec[Maxi].first << " " << Max << endl;

    return 0;
}

