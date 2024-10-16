#include"UdpServer.hpp"
#include"Dict.hpp"
#include<memory>

using namespace log_ns;

//./udp_server local-ip local-port
//./udp_server 127.0.0.1 8888lll
int main(int argc,char *argv[])
{
    if(argc != 2 )
    {
        std::cerr << "Usage: " << argv[0] << "local-port" << std::endl;   //使用手册，不再用IP地址了
        exit(0);
    }

    uint16_t port = std::stoi(argv[1]);
    // std::string ip = argv[1];       //端口号
    // uint16_t port std::stoi(argv[2]);   //本主机：localhost
    EnableScreen();

    Dict dict("./dict.txt");
    func_t Translate = std::bind(&Dict::Translate,&dict,std::placeholders::_1);


    std::unique_ptr<UdpServer> usvr = std::make_unique<UdpServer>(Translate,port); //C++14的标准
    usvr->InitServer();
    usvr->Start();

    return 0;
}