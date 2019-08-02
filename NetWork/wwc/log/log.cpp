#include <iostream>
#include "log.h"


void log::operator<<(std::string s) {
    if(log_file.is_open()) {
        log_file.write(s.c_str(),s.size());
    }
}
log::~log()
{
    log_file.close();
}

