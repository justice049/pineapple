#include<iostream>
#include<unistd.h>
#include"Thread.hpp"

using namespace ThreadMoudle;

void Print(const std::string &name)
{
    int cnt = 1;
    while (true)
    {
        std::cout << name << "is running" << std::endl;
        sleep(1);
    }
    
}

int main()
{
    Thread t("thread-1",Print);
    t.Start();

    std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    t.Stop();
    sleep(1);
    std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    sleep(1);
    t.Join();
    std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    return 0;
}