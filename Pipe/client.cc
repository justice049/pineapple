#include"namedPiped.hpp"

int main()
{
    NamePiped fifo(comm_path,User);
    if(fifo.OpenForWrite())
    {
        while(true)
        {
            std::cout << "Please Enteer -> ";
            std::string message;
            std::getline(std::cin,message);     //从标准输入中获取信息到message中
            fifo.WriteNamedPipe(message);
        }
    }
    return 0;
}