#include "Parsing.h"
int main()
{

    string file = "Gram";
    Parsing Ps(file);
    Ps.ExtractLeftFactor();
    Ps.LeftRecursion();

    string x = "R->Sa|a";
    string y = "S->Qc|c";
    Ps.Replace(x,y);
    cout << x << endl << y << endl;
    return 0;
}

