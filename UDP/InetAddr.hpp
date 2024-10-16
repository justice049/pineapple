#pragma once

#include<iostream>
#include<string>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

class InetAddr
{
private:
    void ToHost(const struct sockaddr_in &addr)
    {
        _port = ntohs(addr.sin_port);   //收到的网络序列转主机，让它正确的显示出来
        _ip = inet_ntoa(addr.sin_addr);      //将四字节的地址转为字符串
    }
public:
    InetAddr(const struct sockaddr_in &addr):_addr(addr)
    {
        ToHost(_addr);
    }
    std::string Ip()
    {
        return _ip;
    }
    uint16_t Port()
    {
        return _port;
    }
    ~InetAddr()
    {
        //析构呵呵
    }
private:
    std::string _ip;
    uint16_t _port;
    struct sockaddr_in _addr;   //不确定以后要什么格式的，先预设着到时候也好转
};