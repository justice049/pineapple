#include"Shm.hpp"
#include"namedPiped.hpp"

int main()
{
    //又是一天，什么都没有改变
    //创建共享内存
    Shm shm(gpathname,gproj_id,gCreater);
    char* shmaddr = (char*)shm.Addr(); 

    //创建管道
    NamePiped fifo(comm_path,Creater);
    fifo.OpenForRead();

    shm.DebugShm();

    while (true)
    {
        std::string temp;
        fifo.ReadNamedPipe(&temp);
        
        std::cout << "shm memory content: " << shmaddr <<std::endl;
        sleep(1);
    }
    
    return 0;
}