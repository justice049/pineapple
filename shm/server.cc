#include"Shm.hpp"

int main()
{
    //又是一天，什么都没有改变
    Shm shm(gpathname,gproj_id,gCreater);

    char* shmaddr = (char*)shm.Addr(); 

    while (true)
    {
        std::cout << "shm memory content: " << shmaddr <<std::endl;
        sleep(1);
    }
    
    return 0;
}