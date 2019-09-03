#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int n,s,num;
    cin >> n >> s >> num;
    
    vector<pair<int,vector<int>>> vec;

    char ch;
    int k = 0;
    int p = n-1;

    for(int i = 0;i != num;++i) {
        cin >> ch;
        for(int j = 0;j != 6;++j) {
            vector<int> v;
            for(int x = 0;x != 4;++x) {
                int nums[2];
                cin >> nums[0];
                cin >> nums[1];
                int value = nums[0]*8+nums[1];
                v.push_back(value);
            }
            vec.push_back(pair<int,vector<int>>(k,v));
             
        }
    }

    return 0;
}

