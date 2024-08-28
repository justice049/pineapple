#include"namedPiped.hpp"

int main()
{
    NamePiped fifo(comm_path,Creater);
    if(fifo.OpenForRead())
    {
        while(true)
        {
            std::string message;
            int n = fifo.ReadNamedPipe(&message);
            if(n > 0)
            {
                std::cout << "Client Say " << message << std::endl;
            }
            else if(n == 0)
            {
                std::cout << "Client quit, Server Too!" << std::endl;
                break;
            }
            else
            {
                std::cout << "fifo.ReadNamePipe Error" << std::endl;
                break;
            }
        }
    }
    return 0;
}