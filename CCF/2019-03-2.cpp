#include <iostream>
#include <vector>
using namespace std;

bool IsTrue(string s) {
    vector<int> nums;
    vector<char> signs;
    nums.push_back(s[0]-'0');
    for(size_t i = 1;i != s.size();++i) {
        if(s[i] >= '0' && s[i] <= '9') {
            nums.push_back(s[i]-'0');
        }
        else {
            switch(s[i]) {
            case '+':
            case '-':
                signs.push_back(s[i]);
                break;
            case 'x':
                nums[nums.size()-1] = nums[nums.size()-1]*(s[i+1] - '0');
                i++;
                break; 
            case '/':
                nums[nums.size()-1] = nums[nums.size()-1]/(s[i+1] - '0');
                i++;
                break; 
            }
        }

    }

    int sum = nums[0];
    if(signs.size() == 0) {

    }
    else {

        for(size_t i = 1,j = 0;i != nums.size();++i,++j) {
            switch(signs[j]) {
            case '+':
                sum += nums[i];
                break;
            case '-':
                sum -= nums[i];
                break;
            }
        }
    }

    return sum == 24;

}
int main()
{
    int n;
    cin >> n;
    vector<string> ar;
    for(int i = 0;i != n;++i) {
        string t;
        cin >> t;
        ar.push_back(t);
    }
    
    for(int i = 0;i != n;++i) {
        if(IsTrue(ar[i])) {
            cout << "Yes" << endl;
        }
        else
            cout << "No" << endl;
    }
    return 0;
}

