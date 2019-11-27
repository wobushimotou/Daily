#include "Parsing.h"
int main()
{
    string file = "Gram";
    Parsing Ps(file);
    Ps.LeftFactor();
    Ps.LeftRecursion();

    return 0;
}

