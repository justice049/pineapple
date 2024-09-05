#define __SHM_HPP__
#ifdef __SHM_HPP__

#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<cerrno>
#include<cstdio>
#include<cstring>
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
        _shmid = shmget(_key,gShmSize,IPC_CREAT | 0666);   //不用IPC_EXCL,避免在已经存在的时候出错
        //调试代码，我看看权限是什么，会不会是显示的问题
        struct shmid_ds shm_info;
        if (shmctl(_shmid, IPC_STAT, &shm_info) == -1) 
        {
            perror("shmctl IPC_STAT");
        } 
        else 
        {
            std::cout << "Created Shm Permissions: " << std::oct << shm_info.shm_perm.mode << std::endl;
        }
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
        _shmid = shmget(_key,gShmSize,IPC_CREAT | 0666);    //哈哈，真是令人忍俊不禁
        struct shmid_ds shm_info;
        
        //调试代码，我看看权限是什么，会不会是显示的问题
        if (shmctl(_shmid, IPC_STAT, &shm_info) == -1) 
        {
            perror("shmctl IPC_STAT");
        } 
        else 
        {
            std::cout << "Created Shm Permissions: " << std::oct << shm_info.shm_perm.mode << std::endl;
        }
        
        if(_shmid >= 0)
        {
            return true;
        }
    }
    return false;
}

// // 更改共享内存权限，我先注释掉
// void SetShmPermissions(int shmid, mode_t perms)
// {
//     struct shmid_ds shm_info;
//     if (shmctl(shmid, IPC_STAT, &shm_info) == -1)
//     {
//         perror("shmctl IPC_STAT");
//         return;
//     }

//     shm_info.shm_perm.mode = perms;
//     if (shmctl(shmid, IPC_SET, &shm_info) == -1)
//     {
//         perror("shmctl IPC_SET");
//     }
// }

void *AttachShm()
{
    if(_addrshm != nullptr)
    {
         DetachShm(_addrshm);
    }
    void *shmaddr = shmat(_shmid,nullptr,0);  
    if(shmaddr == (void*)-1)
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

void Zero()
{
    if(_addrshm)
    {
        memset(_addrshm,0,gShmSize);
    }
}

void *Addr()
{
    return _addrshm;
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
