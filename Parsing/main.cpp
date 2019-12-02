#include "Parsing.h"
int main()
{

    string file = "Gram";
    Parsing Ps(file);
    Ps.ExtractLeftFactor();

    Ps.LeftRecursion();

    return 0;
}

