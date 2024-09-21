#include<iostream>
#include<vector>
#include<unistd.h>
#include<cstdio>
#include"Thread.hpp"

using namespace ThreadMoudle;

//抢票要有全部的票数
int tickets = 10000;

void route(const std::string &name)
{
    while (true)
    {
        if(tickets > 0)
        {
            //抢票过程
            usleep(1000);       // 1ms -> 抢票花费的时间，这里暂时用这个休眠函数模拟
            printf("%s get ticket:%d\n",name.c_str(),tickets);          //是谁没有抢到票
            tickets--;
        }
        else
        {
            break;
        }
    }
    
}

int main()
{
    Thread t1("thread-1",route);
    Thread t2("thread-2",route);
    Thread t3("thread-3",route);
    Thread t4("thread-4",route);
    
    t1.Start();
    t2.Start();
    t3.Start();
    t4.Start();

    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();
    return 0;
}