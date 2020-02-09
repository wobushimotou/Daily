#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main()
{
    char buf[] = "wanghengg";
    fstream out("1.txt");
    
    out.seekp(10,ios::beg);

    out.write(buf,10);


    out.close();
    return 0;
}

