#include"UdpServer.hpp"
#include"Log.hpp"
#include<memory>

using namespace log_ns;

int main()
{
    uint16_t port = 8899;       //端口号
    std::string ip = "127.0.0.1"    //本主机：localhost
    EnableScreen();
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(ip,port); //C++14的标准
    usvr->InitServer();
    usvr->Start();
    return 0;
}