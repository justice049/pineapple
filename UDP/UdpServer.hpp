#pragma once

#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>

#include"nocopy.hpp"
#include"Log.hpp"

using namespace log_ns;

static const int gsockfd = -1; 

//让我们来枚举一些常量罢
enum
{
    SOCKET_ERROR = 1
};


class UdpServer : public nocopy
{
public:
    UdpServer():_sockfd(gsockfd)
    {

    }
    void InitServer()
    {
        //创建socket文件
        _sockfd = ::socket(AF_INET,SOCK_DGRAM,0);   //网络套接字，用户，协议类型
        if(_sockfd<0)
        {
            LOG(FATAL,"socket error\n");
            exit(SOCKET_ERROR);
        }
        LOG(DEBUG,"socket create sucess,_sockfd:%d\n",_sockfd);     //当然是3，其实当013都不如4了让人刺激
    }
    void Start()
    {

    }
    ~UdpServer()
    {

    }
private:
    int _sockfd;

};
