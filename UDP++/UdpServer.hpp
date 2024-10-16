#pragma once

#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<cstring>
#include<string>
#include<functional>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#include"nocopy.hpp"
#include"Log.hpp"
#include"InetAddr.hpp"

using namespace log_ns;

static const int gsockfd = -1; 
static const uint16_t glocalport = 8888; 

//让我们来枚举一些常量罢
enum
{
    SOCKET_ERROR = 1,
    BIND_ERROR
};

using func_t = std::function<std::string(std::string)>;     //这是个模板
//UdpServer user("192.1.1.1",8899);
class UdpServer : public nocopy
{
public:
    UdpServer(func_t func,uint16_t localport = glocalport)
    :_func(func),
    _sockfd(gsockfd),
    _localport(localport),
    _isrunning(false)
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
        
        //local.sin_addr.s_addr = inet_addr(_localip.c_str());            //需要四字节的IP  需要网络序列的IP，暂时的信号捏
        
        local.sin_addr.s_addr = INADDR_ANY;         //建议写成INADDR_ANY,就是服务器端进行任意IP地址绑定

        int n = ::bind(_sockfd,(struct sockaddr*)&local,sizeof(local));
        if(n<0)
        {
            LOG(FATAL,"bind error\n");
            exit(BIND_ERROR);
        }
        LOG(DEBUG,"socket bind success\n");
    }
    void Start()
    {
        _isrunning = true;
        char inbuffer[1024];
        while (_isrunning)
        {
            struct sockaddr_in peer;    //谁给我发的信息
            socklen_t len = sizeof(peer);
            ssize_t n = recvfrom(_sockfd,inbuffer,sizeof(inbuffer)-1,0,(struct sockaddr*)&peer,&len);
            if(n>0)
            {
                InetAddr addr(peer);
                //这是回调函数，要返回的
                //读到了，要发消息
                inbuffer[n]=0;

                std::cout << "[" << addr.Ip() << ":" << addr.Port() << "]# " << inbuffer << std::endl;
                
                std::string result = _func(inbuffer);
                //std::string echo_string = "[udp_server echo]#";
                //echo_string += inbuffer;

                sendto(_sockfd,result.c_str(),result.size(),0,(struct sockaddr *)&peer,len);
            }
            else
            {
                std::cout << "recvfrom error" << std::endl;
            }
        }
    }
    ~UdpServer()
    {
        if(_sockfd>gsockfd)
        ::close(_sockfd);        //大于默认的就关闭了
    }
private:
    int _sockfd;
    uint16_t _localport;
    //std::string _localip;   //IP地址
    func_t _func;
    bool _isrunning; 
};
