#pragma once
#include <string>
#include <iostream>
#include <fstream>

class log
{
public:
    log(std::string filename = "./log_file") : log_file(filename,std::ios::app) {  }
    ~log();
    void operator<<(std::string s);
    void operator<<(int num);
    void operator<<(size_t num);

private:
    std::fstream log_file;
};


