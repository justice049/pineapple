#include"UdpServer.hpp"
#include"Log.hpp"
#include<memory>

using namespace log_ns;

int main()
{
    EnableScreen();
    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>();
    usvr->InitServer();
    usvr->Start();
    return 0;
}