#include"UdpServer.hpp"
#include<memory>

//客户端在未来一定要知道服务器的IP地址和端口号
//./udp_server server-ip server-port
//./udp_server 127.0.0.1 8888

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Usage" << argv[0] << "server-ip server-port" << std::endl;
        exit(0);
    }

    std::string serverip = argv[1];
    uint16_t serverport =  std::stoi(argv[2]);


    int sockfd = ::socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
    {
        std::cerr << "create socket error" << std::endl;
        exit(1);
    }

    //client的端口号一般不让用户自己设定，而是OS随机选择
    //bind          client需不需要绑定自己的IP和端口呢？

    if(sockfd < 0)
    {
        std::cerr << "create socket error" << std::endl;
        exit(1);
    }

    struct sockaddr_in server;
    memset (&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = serverport;
    server.sin_addr.s_addr = inet_addr(serverip.c_str());


    while(1)
    {
        std::string line;
        std::cout << "Please Enter# ";
        std::getline(std::cin,line);

        int n = sendto(sockfd,line.c_str(),line.size(),0,(struct sockaddr*)&server,sizeof(server));      //要知道发送消息发给谁

        if(n>0)
        {
            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            char buffer[1024];
            int m = recvfrom(sockfd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&temp,&len);
            if(m > 0)
            {
                buffer[m] = 0;
                std::cout << buffer << std::endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }


    ::close(sockfd);
    return 0;
}