#include <iostream>

using namespace std;

void fun(int *nums,int sum,int level,char *a) {
    if(sum == 24) {
        for(int i = 0;i != 3;++i) {
            cout << nums[i] << a[i];
        }
        cout << nums[3] << endl;
    }
    if(level == 3)
        return;

    a[level] = '+';
    fun(nums,sum+nums[level+1],level+1,a);

    a[level] = '-';
    fun(nums,sum-nums[level+1],level+1,a);

    a[level] = '*';
    fun(nums,sum*nums[level+1],level+1,a);
    
    a[level] = '/';
    fun(nums,sum/nums[level+1],level+1,a);

    cout << "NONE" << endl;
}
int main()
{
    string ar[4];

    for(int i = 0;i != 4;++i)
        cin >> ar[i];


    for(int i = 0;i != 4;++i)
        if(ar[i] == "joker" || ar[i] == "JOKER") {
            cout << "ERROR" << endl;
            return 0;
        }

    int nums[4];
    for(int i = 0;i != 4;++i) {
        char letter = ar[i][0];
        if(ar[i][0] >= '2' && ar[i][0] <= '9')
            nums[i] = ar[i][0] - '0';
        
        if(letter == '1')
            nums[i] = 10;
        if(letter == 'J')
            nums[i] = 11;
        if(letter == 'Q')
            nums[i] = 12;
        if(letter == 'K')
            nums[i] = 13;
        if(letter == 'A')
            nums[i] = 1;
    }

    char a[3];
    fun(nums,0,0,a);

    return 0;
}

