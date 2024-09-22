#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdio>
#include "Thread.hpp"

using namespace ThreadMoudle;

// 抢票要有全部的票数
int tickets = 10000;
pthread_mutex_t gmutex = PTHREAD_MUTEX_INITIALIZER;

void route(ThreadData *td)
{
    while (true)
    {
        // 加锁
        pthread_mutex_lock(td->_lock);
        if (tickets > 0)
        {
            // 抢票过程
            usleep(1000);                                             // 1ms -> 抢票花费的时间，这里暂时用这个休眠函数模拟
            printf("%s get ticket:%d\n", td->_name.c_str(), tickets); // 是谁没有抢到票
            tickets--;
            pthread_mutex_unlock(td->_lock); // 解锁
        }
        else
        {
            pthread_mutex_unlock(td->_lock); // 解锁
            break;
        }
    }
}

// void route(const std::string &name)
// {
//     while (true)
//     {
//         //加锁
//         pthread_mutex_lock(&gmutex);
//         if(tickets > 0)
//         {
//             //抢票过程
//             usleep(1000);       // 1ms -> 抢票花费的时间，这里暂时用这个休眠函数模拟
//             printf("%s get ticket:%d\n",name.c_str(),tickets);          //是谁没有抢到票
//             tickets--;
//             pthread_mutex_unlock(&gmutex);      //解锁
//         }
//         else
//         {
//             pthread_mutex_unlock(&gmutex);      //解锁
//             break;
//         }
//     }
// }

static int threadnum = 4;

int main()
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);

    std::vector<Thread> threads;
    for (int i = 0; i < threadnum; i++)
    {
        std::string name = "thread-" + std::to_string(i + 1);
        ThreadData *td = new ThreadData(name, &mutex);
        threads.emplace_back(name, route, td);
    }
    for (auto &thread : threads)
    {
        thread.Start();
    }
    for (auto &thread : threads)
    {
        thread.Join();
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}

// int main()
// {
//     Thread t1("thread-1",route);
//     Thread t2("thread-2",route);
//     Thread t3("thread-3",route);
//     Thread t4("thread-4",route);

//     t1.Start();
//     t2.Start();
//     t3.Start();
//     t4.Start();

//     t1.Join();
//     t2.Join();
//     t3.Join();
//     t4.Join();
//     return 0;
// }