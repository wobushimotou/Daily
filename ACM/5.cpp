#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> nums;
long GetNum(long left,long right,int flag) {
    long sum = 0;
    for(int i = left;i <= right;++i)
        if(nums[i] == flag)
            sum += 1;
    return sum;
}

long GetLongest(long size) {
   long Max = 0;
    for(long k = 1;k < size;++k) {
        long temp = GetNum(0,k,0) + GetNum(k+1,size-1,1);
        if(Max < temp)
            Max = temp;
    }
    return Max;  
}

void Replace(long left,long right) {
    for(int i = left-1;i <= right-1;++i) {
        if(nums[i] == '0')
            nums[i] = 1;
        else
            nums[i] = 0;
    }
    for(auto &e:nums)
        cout << e;
    cout << endl;
}
int main()
{
    long size;
    int c_size;
    cin >> size;
    cin >> c_size;

    string num;
    cin >> num;

    for(int i = 0;i < size;++i) {
        nums.push_back(num[i]-'0');
    }
  
    string cc;
    for(int i = 0;i < c_size;++i) {
        getline(cin,cc);
        if(cc[0] == 'q')
            cout << GetLongest(size) << endl;
        else if(cc[0] == 'c'){
            long left = cc[2]-'0';
            long right = cc[4]-'0';

            for(int n = left-1;n < right;++n)
                if(nums[n] == 0)
                    nums[n] = 1;
                else
                    nums[n] = 0;
        
        }

    }
    return 0;
}

