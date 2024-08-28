#define __SHM_HPP__
#ifdef __SHM_HPP__

#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<cerrno>
#include<cstdio>
#include<string>

const int gCreater = 1;
const int gUser = 2;

class Shm
{
public:
    Shm(const std::string &pathname, int proj_id)
    :_pathname(pathname),_proj_id(proj_id)
    {};
    ~Shm();
key_t GetCommKey()
{
    key_t k = ftok(_pathname.c_str(),_proj_id);
     if(k < 0)
     {
        perror("ftok");
     }
     return k;
}
//转十六进制捏
std::string ToHex()
{
    char buffer[128];
    snprintf(buffer,sizeof(buffer),"0x%x",_key);
    return buffer;
}
//创建共享内存
int ShmGet(key_t key,int size)
{
    int shmid = shmget(key,size,IPC_CREAT | IPC_EXCL);
    if(shmid < 0)
    {
        perror("shmget");
    }
    return shmid;
}
private:
    key_t _key;
    int _shmid;
    std::string _pathname;
    int _proj_id;
    int _who;
};










#endif 