#include <iostream>
#include <functional>

using namespace std;

std::string onGet(std::string buff) {
    size_t begin = buff.find("Referer");
    size_t end = buff.find("\r\n",begin);
    int i = buff.substr(begin,end-begin).find_last_of("/");
    return buff.substr(begin,end-begin).substr(i+1,end-begin-i);
}


int main()
{
    string buff = std::string("GET /favicon.ico HTTP/1.1\r\n") + \
                "Host: 192.168.3.34:11111\r\n" + \
                "Connection: keep-alive\r\n" + \
                "Referer: http://192.168.3.34:11111/index.html\r\n" + \
                "Accept-Encoding: gzip, deflate\r\n" + \
                "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n\r\n";
    cout << onGet(buff) << endl;

    
    return 0;
}

