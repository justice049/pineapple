#include"Shm.hpp"
#include"namedPiped.hpp"

int main()
{
    //创建共享内存
    Shm shm(gpathname,gproj_id,gUser);
    char* shmaddr = (char*)shm.Addr(); 

    //打开管道
    NamePiped fifo(comm_path,User);
    fifo.OpenForWrite();

    char ch = 'A';
    while (ch <= 'Z')
    {
        shmaddr[ch - 'A'] = ch;
        ch++;
        std::string temp = "wakeup";
        std::cout << "add" << ch << "into Shm, " << "wakeup reader" << std::endl;

        fifo.WriteNamedPipe(temp);

        sleep(1);
    }
    
    return 0;
}