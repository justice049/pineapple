#include"Shm.hpp"

int main()
{
    Shm shm(gpathname,gproj_id,gUser);
    char* shmaddr = (char*)shm.Addr(); 

    char ch = 'A';
    while (ch <= 'Z')
    {
        shmaddr[ch - 'A'] = ch;
        ch++;
        sleep(1);
    }
    
    return 0;
}