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
                std::cout << "Client Say> " << message << std::endl;
            }
        }
    }
    return 0;
}