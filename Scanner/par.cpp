#include <iostream>
#include <algorithm>
#include "scanner.cpp"
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main()
{
    Scan sc("test.c");
    sc.Scanner();
    sc.Display();
    return 0;
}



