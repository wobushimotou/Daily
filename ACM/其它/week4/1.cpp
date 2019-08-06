/*
 *  查作弊问题
 *  若Ａ回答了B的问题，Ｂ也回答了Ａ的问题，则视两人为作弊
 *  若作弊用户Ａ，作弊用户Ｂ同时回答了Ｃ的问题，则视Ｃ也为作弊
 *  给出每个问题的回答人员，得出总共有多少人作弊
 *
 * */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<pair<int,vector<int>>> vec;
    multimap<int,int> imap;
    vector<int> nums;

    for(int i = 0;i < n;++i) {
        int r,m;
        cin >> r >> m;
        vec.push_back(pair<int,vector<int>>(r,{}));
        for(int j = 0;j < m;++j) {
            int id;
            cin >> id;
            vec[i].second.push_back(id);
            imap.insert(make_pair(r,id));
        }
    }

    for(int i = 0;i < n;++i) {
        int r = vec[i].first;
        for(size_t j = 0;j < vec[i].second.size();++j) {
            int s = vec[i].second.at(j);
            auto p = imap.find(s);            
            int count = imap.count(s);
            for(int x = 0;x < count;++x)
                if(p->second == r) {
                    if(find(nums.begin(),nums.end(),r) == nums.end())
                        nums.push_back(r);
                    if(find(nums.begin(),nums.end(),s) == nums.end())
                        nums.push_back(s);
                }
        }
    }
    

    for(int i = 0;i < n;++i) {
        int r = vec[i].first;
        int flag = 0;
        if(find(nums.begin(),nums.end(),r) != nums.end())
            continue;
        for(size_t j = 0;j < vec[i].second.size();++j) {
            int s = vec[i].second.at(j);
            if(find(nums.begin(),nums.end(),s) != nums.end())
                flag++;
            if(flag == 2) {
                nums.push_back(r);
                break;
            }
        }
    }

    std::cout << nums.size() << std::endl;
    for(auto p = nums.begin();p != nums.end();++p)
        std::cout << *p << " ";



    return 0;
}

