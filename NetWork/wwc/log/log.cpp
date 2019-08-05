#include <iostream>
#include "log.h"


void log::operator<<(std::string s) {
    if(!log_file.is_open())
        log_file.open("../log_file",std::ios::app);
    log_file.write(s.c_str(),s.size());
}

void log::operator<<(int num) {
    std::string s = std::to_string(num);
    this->operator<<(s);
}

void log::operator<<(size_t num) {
    std::string s = std::to_string(num);
    this->operator<<(s);
}


log::~log()
{
    log_file.close();
}

