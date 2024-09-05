#include"Shm.hpp"

int main()
{
    Shm shm(gpathname,gproj_id,gUser);
    char*addr = (char*)shm.AttachShm();
    sleep(3);
    return 0;
}