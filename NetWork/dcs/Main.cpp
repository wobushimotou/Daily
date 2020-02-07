#include <iostream>
#include "../wwc/EventLoop.h"
#include "../wwc/TcpServer.h"

int main()
{
    std::shared_ptr<EventLoop> loop = std::make_shared<EventLoop>();
    TcpServer server(loop,8888,"wh");
    return 0;
}

