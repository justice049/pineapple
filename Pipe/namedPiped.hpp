#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<cerrno>
#include<cstdio>
#include<unistd.h>
#include<string>
#include<fcntl.h>

#define DefaultFd -1
#define Creater 1
#define User 2
#define Read O_RDONLY
#define Write O_WRONLY
#define BaseSize 4096

const std::string comm_path = "./myfifo";

class NamePiped
{
private:
    //打开文件的模式
    bool OpenNamedPipe(int mode)
    {
        _fd = open(_fifo_path.c_str(),mode);
        if(_fd < 0)
        {
            return 0;
        }
        return true;
    }
public:
    NamePiped(const std::string &path,int who)
    :_fifo_path(path), _id(who),_fd(DefaultFd)
    {
        if(_id == Creater)
        {
            int res = mkfifo(path.c_str(),0666);
            if(res != 0)
            {
              perror("mkfifo");
            }
        }
    }
    bool OpenForRead()
    {
        return OpenNamedPipe(Read);
    }
    bool OpenForWrite()
    {
        return OpenNamedPipe(Write);
    }
    
    //输出：const &:const std::string &XXX
    //输入：*      std::string *
    //输入输出：&   std::string &

    int ReadNamedPipe(std::string *out)
    {
        char buffer[BaseSize];
        int n = read(_fd,buffer,sizeof(buffer));
        if(n > 0)
        {
            //读取成功
            buffer[n] = 0;
            *out = buffer;
        }
        return n;
    }
    int WriteNamedPipe(const std::string &in)
    {
        write(_fd,in.c_str(),in.size());
        
    }
    ~NamePiped()
    {
        if(_id == Creater)
        {
            int res = unlink(_fifo_path.c_str());
            if(res != 0)
            {
                perror("unlink");
            }
        }
        if(_fd != DefaultFd)
        {
            close(_fd);
        }
    }
private:
    const std::string _fifo_path;
    int _id;
    int _fd;
};
