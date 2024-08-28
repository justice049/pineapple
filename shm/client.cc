#include"Shm.hpp"

int main()
{
    key_t key = GetCommKey(pathname,proj_id);
    std::cout << "key:" << ToHex(key) << std::endl;
    return 0;
}