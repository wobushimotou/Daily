#include <iostream>
#include "Buddy.h"
int main()
{
    Buddy bd(532);
    bd.Init();
    bd.Display();
    cout << endl;
    int *tt = (int *)bd.Apply(18);
    bd.Display();
    return 0;
}

