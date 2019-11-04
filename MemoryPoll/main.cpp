#include <iostream>
#include "Buddy.h"
int main()
{
    Buddy bd(532);
    bd.Init();
    bd.Display();
    cout << endl;
    int *t = (int*)bd.Apply(4);
    bd.Display();
    cout << endl;
    bd.Release(t,sizeof(int));
    bd.Display();
    return 0;
}

