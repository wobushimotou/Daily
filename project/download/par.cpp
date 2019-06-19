#include <iostream>
#include <fstream>


int main()
{
    std::fstream f("1.txt");
    f << "1234456";
    f.close();
    return 0;
}

