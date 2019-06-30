#include <iostream>
#include <vector>

using namespace std;
double f(vector<int>& nums1,vector<int>& nums2)
{
    int flag;
    int i = 0,j = 0;
    int m =nums1.size();
    int n = nums2.size();
    while(i + j + 1 < (m+n)/2) {
        if(nums1[i] > nums2[j]) {
            ++j;
            flag = 1;
        }
        else {
            ++i;
            flag = 0;
        }
    }
    if((m+n)%2 == 0) {
        if(flag)
            return (nums2[j]+max(nums2[j+1],nums1[i]))/2.0;
        else
            return (nums1[i]+max(nums1[i+1],nums2[j]))/2.0;

    }
    else {    
        if(flag)
            return nums2[j];
        else
            return nums1[i];
    }

}

int main()
{
    vector<int> v1 = {1,2};
    vector<int> v2 = {3,4};
    cout << f(v1,v2) << endl;
    return 0;
}

