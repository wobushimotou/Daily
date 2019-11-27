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
    void ExtractSign(); //提取终结符和非终结符
    void ExtractLeftFactor();  //提取左公因子
    void DirectLeftRecursion();   //消除直接左递归
    void LeftRecursion();   //消除间接左递归
    char GetNextSign(); //从文法中得到下一个可用符号
    
    bool IsendSign(char ch) {
        return (find(endSigns.begin(),endSigns.end(),ch) != endSigns.end());
    }

    void Replace(string &,string);
    ~Parsing() {}
private:
    string filename;
    string signs;
    vector<char> endSigns;
    vector<char> nonendSigns;
};

