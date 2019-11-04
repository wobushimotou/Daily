#pragma once
#include <deque>
#include <vector>
#include <memory>
#include <iostream>
#include <any>
#include <math.h>

using Space = unsigned char;
using namespace std;
class Buddy
{
public:
    Buddy(int _size);
    Buddy();

    //初始化内存池
    void Init();
    //输出此时内存占用情况
    void Display();

    void *Apply(int size);
    void Alloc(int address,int size);
    void Release(void *address,size_t size);
    ~Buddy();
    int GetMaxBit(int);
    int NumToBitNum(int);
private:
    int size;
    unique_ptr<Space[]> area;
    vector<deque<int>> mm;    
};

