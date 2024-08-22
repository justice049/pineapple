#include"namedPiped.hpp"

int main()
{
    NamePiped fifo(comm_path,User);
    fifo.OpenForWrite();
    return 0;
}