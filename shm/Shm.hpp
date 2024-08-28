#define __SHM_HPP__
#ifdef __SHM_HPP__

#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<cerrno>
#include<cstdio>
#include<string>

const std::string pathname = "/root/ice/pineapple/shm";
const int proj_id = 0x49;

key_t GetCommKey(const std::string &pathname,int proj_id)
{
    key_t k = ftok(pathname.c_str(),proj_id);
     if(k < 0)
     {
        perror("ftok");
     }
     return k;
}

//转十六进制捏
std::string ToHex(key_t k)
{
    char buffer[128];
    snprintf(buffer,sizeof(buffer),"0x%x",k);
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

#endif 