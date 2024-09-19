#include <iostream>
#include<string>
#include<vector>
#include<pthread.h>
#include<thread>
#include<stdlib.h>
#include <unistd.h>

void threadRun(std::string name,int num)
{
    while (num)
    {
        std::cout << name << " num: " << num << std::endl;
        num--;
        sleep(1);
    }
    
}

int main()
{
    std::string name = "thread-1";
    std::thread mythread(threadRun, name ,10);
    while (true)
    {
        std::cout << "main thread..." << std::endl;
    }
    
    mythread.join();
    return 0;
}
