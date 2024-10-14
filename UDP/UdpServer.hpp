#pragma once

#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<cstring>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#include"nocopy.hpp"
#include"Log.hpp"

using namespace log_ns;

static const int gsockfd = -1; 
static const uint16_t glocalport = 8888; 

//让我们来枚举一些常量罢
enum
{
    SOCKET_ERROR = 1
};


class UdpServer : public nocopy
{
public:
    UdpServer(uint16_t localport = glocalport):_sockfd(gsockfd),_localport(localport)
    {

    }
    void InitServer()
    {
        //1.创建socket文件
        _sockfd = ::socket(AF_INET,SOCK_DGRAM,0);   //网络套接字，用户，协议类型
        if(_sockfd<0)
        {
            LOG(FATAL,"socket error\n");
            exit(SOCKET_ERROR);
        }
        LOG(DEBUG,"socket create sucess,_sockfd:%d\n",_sockfd);     //当然是3，其实当013都不如4了让人刺激

        //2.bind
        struct sockaddr_in local;
        memset(&local,0,sizeof(local));
        local.sin_family = AF_INET;     //要和上面的一样
        local.sin_port = htons(_localport);        //主机序列转网络序列
        local.sin_addr=
    }
    void Start()
    {

    }
    ~UdpServer()
    {

    }
private:
    int _sockfd;
    uint16_t _localport;
    std::string _localip;   //IP地址
};
