#include<iostream>
#include<unistd.h>
#include<vector>
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

const int num = 10;

int main()
{
    //构建线程
    std::vector<Thread> threads;
    for(int i=0;i<num;i++)
    {
        std::string name = "thread";
        threads.emplace_back(name,Print);
    }
    //统一启动
    for(auto &thread:threads)
    {
        thread.Start();
    }
    sleep(5);
    //统一结束，好像集中营，我们都是
    for(auto &thread:threads)
    {
        thread.Stop();
    }
    //等待线程
    for(auto &thread:threads)
    {
        thread.Join();
    }
    // Thread t("thread-1",Print);
    // t.Start();

    // std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    // t.Stop();
    // sleep(1);
    // std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    // sleep(1);
    // t.Join();
    // std::cout << t.Name() << ", status: " << t.Status() << std::endl;
    return 0;
}