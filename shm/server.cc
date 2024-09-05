#include"Shm.hpp"

int main()
{
    //又是一天，什么都没有改变
    Shm shm(gpathname,gproj_id,gCreater);
    char* addr = (char*)shm.AttachShm();
    sleep(3);
    return 0;
}