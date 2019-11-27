/*
 *  LL(1)型文法分析器
 * */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
class Parsing
{
public:
    Parsing(const string &file):filename(file) {}
    void LeftFactor();  //消除左公因子
    char GetNextSign(); //从文法中得到下一个可用符号
    ~Parsing() {}

private:
    string filename;
    string signs;
};

