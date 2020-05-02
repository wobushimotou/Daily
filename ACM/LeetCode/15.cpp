/*
 *  给定数组,找出所有三个数之和为零的组合
 *
 * */
#include <iostream>
#include "InitVec.cpp"
struct Result{
    int m;
    int n;
    int k;
};
vector<Result> vec;
void function(vector<int> &nums) {
    sort(nums.begin(),nums.end());
    int left;
    int right;
    for(size_t i = 0;i < nums.size()-2;) {
        left = i+1;
        right = nums.size()-1;
        while(left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if(sum == 0) {
                vec.push_back({nums[i],nums[left],nums[right]});
            }
            
            if(sum >= 0) {
                while(left < right && nums[right] == nums[--right]);
            }
            else {
                while(left <  right && nums[left] == nums[++left]);
            }
        } 

        while(nums[i] == nums[++i]);
    } 
}

int main()
{
    vector<int> nums;
    GetRandVec(nums,10,-5,5);
    function(nums);
    for(auto &e:vec)
        cout << e.k << " " << e.m << " " << e.n << endl;
    return 0;
}

