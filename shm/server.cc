#include"Shm.hpp"

int main()
{
    key_t key = GetCommKey(pathname,proj_id);
    std::cout << "key:" << ToHex(key) << std::endl;

    int shmid = ShmGet(key,4096);
    std::cout << "shmid:" << shmid << std::endl;

    return 0;
}