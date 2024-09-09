#include<iostream>
#include<unistd.h>
#include<signal.h>

void hander(int sig)
{
    std::cout << "get a sig" << sig <<std::endl;
}

int main()
{
    signal(2,hander);
    while (true)
    {
        std::cout << "hello world,pid: " << getpid() << std::endl;
        sleep(1);
    }
    
    return 0;
}