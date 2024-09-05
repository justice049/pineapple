#define __SHM_HPP__
#ifdef __SHM_HPP__

#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<cerrno>
#include<cstdio>
#include<string>
#include<unistd.h>

const int gCreater = 1;
const int gUser = 2;
const std::string gpathname = "/root/ice/pineapple/shm";
const int gproj_id = 0x49;
const int gShmSize = 4096;

class Shm
{
private:
key_t GetCommKey()
{
    key_t k = ftok(_pathname.c_str(),_proj_id);
     if(k < 0)
     {
        perror("ftok");
     }
     return k;
}
//创建共享内存
// int ShmGet(key_t key,int size,int flag)
// {
//     int shmid = shmget(key,size,flag);
//     if(shmid < 0)
//     {
//         perror("shmget");
//     }
//     return shmid;
// }
std::string RoleToString(int who)
{
    if(who == gCreater)
    {
        return "Creater";
    }
    else if(who == gUser)
    {
        return "User";
    }
    else
    {
        return "None";
    }
}
public:
    Shm(const std::string &pathname, int proj_id,int who)
    :_pathname(pathname),_proj_id(proj_id),_who(who),_addrshm(nullptr)
    {
        _key = GetCommKey();
        if(_who == gCreater) GetShmUserCreate();
        else if(_who == gUser) GetShmForUse();
        _addrshm = AttachShm();
    }
    ~Shm()
    {
        if(_who == gCreater)
        {
            int res = shmctl(_shmid,IPC_RMID,nullptr);
        }
        std::cout << "shm remove done ..." << std::endl;
    }

//转十六进制捏
std::string ToHex()
{
    char buffer[128];
    snprintf(buffer,sizeof(buffer),"0x%x",_key);
    return buffer;
}
bool GetShmUserCreate()
{
    if(_who == gCreater)
    {
        _shmid = shmget(_key,gShmSize,IPC_CREAT | IPC_EXCL | 0666);
        if(_shmid >= 0)
        {
            return true;
        }
        std::cout << "shm create done..." << std::endl;
    }
    return false;
}
bool GetShmForUse()
{
    if(_who == gUser)
    {
        _shmid = shmget(_key,gShmSize,IPC_CREAT);
        if(_shmid >= 0)
        {
            return true;
        }
    }
    return false;
}
void *AttachShm()
{
    if(_addrshm != nullptr)
    {
         DetachShm(_addrshm);
    }
    void *shmaddr = shmat(_shmid,nullptr,0);
    if(shmaddr == nullptr)
    {
        perror("shmat");
    }
    std::cout << "AttachShm " << RoleToString(_who) << std::endl;
    return shmaddr;
}

void DetachShm(void *shmaddr)
{
    if(shmaddr == nullptr)
    {
        return;
    }
    shmdt(shmaddr);
    std::cout << "DetachShm " << RoleToString(_who) << std::endl;
}

private:
    key_t _key;
    int _shmid;
    std::string _pathname;
    int _proj_id;
    int _who;
    void *_addrshm;
};

#endif 