#include <iostream>  
#include<algorithm>  
#include<stdio.h>  
#include<string.h>  
using namespace std;  
  
int main()  
{  
    string s;
    int k;  
    cin >> s;
    cin >> k;

    while(k)  
    {  
        bool flag = true;
        for(size_t i=0;i < s.length();i++) {
            if(s[i] > s[i+1])  
            {  
                s.erase(i,1);
                flag = false;
                break;  
            }  
        }
        if(flag) {
            s.erase(s.length()-1,1);
        }
        k--;
    }  
    std::cout << s << std::endl;
    return 0;
}  
