/*
 *  修改钟表显示时间
 *  若时间显示正常，则不做修改，若不正常，则显示修改最少的数字来达到的最小合理时间
 *
 *
 * */
#include <iostream>
using namespace std;

int main()
{
    string time;
    cin >> time;
    string Hour,Minute,Second;
    Hour = time.substr(0,2);
    Minute = time.substr(3,2);
    Second = time.substr(6,2);
    
    if(Hour[0] > '2') {
        Hour[0] = '0';
    }
    else if(Hour[0] == '2') {
        if(Hour[1] >= '4')
            Hour[1] = '0';
    }

    if(Minute[0] >= '6') {
        Minute[0] = '0';
    }
        
    if(Second[0] >= '6') {
        Second[0] = '0';
    }

    cout << Hour << ":" << Minute << ":" << Second;
    
    return 0;
}

