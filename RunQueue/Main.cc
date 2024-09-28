#pragma once

#include"RunQueue.hpp"
#include"Task.hpp"
#include<iostream>
#include<unistd.h>
#include<string>
#include<pthread.h>

void *Consumer(void* args)
{
    RingQueue<Task> *rq = static_cast<RingQueue<Task>*>(args);
    while (true)
    {
        sleep(1);
        Task t;
        //消费
        rq->Pop(&t);
        //处理数据
        t();
        std::cout << "Consumer -> " << t.result() << std::endl;
    }
}

void* Productor(void* args)
{
    RingQueue<Task> *rq = static_cast<RingQueue<Task>*>(args);
    while (true)
    {
        sleep(1);
        //构造数据
        int x = rand() % 10 + 1;
        int y = rand()%10 + 1;
        Task t(x,y);
        //生产
        rq->Push(t);
        std::cout << "Productor -> " << t.debug() << std::endl;
    }
}

int main()
{
    srand(time(nullptr)^getgid());
    RingQueue<Task> *rq = new RingQueue<Task>(5);

    pthread_t c,p;
    pthread_create(&c,nullptr,Consumer,rq);
    pthread_create(&p,nullptr,Productor,rq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}