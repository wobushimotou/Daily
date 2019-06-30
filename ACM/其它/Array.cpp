#include <iostream>
#include <vector>

using namespace std;

string ar;
void temp(int m,int n)
{
    /*
    ar.at(m) = ar.at(m) + ar.at(n);
    ar.at(n) = ar.at(m) - ar.at(n);
    ar.at(m) = ar.at(m) - ar.at(n);
    */
    char ch = ar.at(m);
    ar.at(m) = ar.at(n);
    ar.at(n) = ch;
}
void array(int start,int end)
{
    if(start == end) {
        cout << ar <<  endl;
        return;
    }
    for(int i = start;i <= end;++i) {
        temp(i,start);
        array(start+1,end); 
        temp(start,i);    
    }        
}
int main()
{
    for(int i = 0;i < 5;++i)
        ar.push_back('a'+i);
    
    array(0,ar.length()-1);

    return 0;
}

