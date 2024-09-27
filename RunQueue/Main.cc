#pragma once

#include"RunQueue.hpp"
#include<iostream>
#include<unistd.h>
#include<string>
#include<pthread.h>

void *Consumer(void* args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int>*>(args);
    while (true)
    {
        sleep(1);
        int data = 0;
        //消费
        rq->Pop(&data);
        //处理数据
        std::cout << "Consumer -> " << data << std::endl;
    }
    
}

void* Productor(void* args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int>*>(args);
    while (true)
    {
        //构造数据
        int data = rand() % 10 + 1;
        //生产
        rq->Push(data);
        std::cout << "Productor -> " << data << std::endl;
    }
}

int main()
{
    RingQueue<int> *rq = new RingQueue<int>(5);

    pthread_t c,p;
    pthread_create(&c,nullptr,Consumer,rq);
    pthread_create(&p,nullptr,Productor,rq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}