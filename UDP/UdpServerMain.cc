#include"UdpServer.hpp"
#include<memory>

int main()
{
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>();
    usvr->InitServer();
    usvr->Start();
    return 0;
}