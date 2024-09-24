#pragma once

#include<iostream>
#include<string>
#include<queue>
#include<pthread.h>

const static int defaultcap = 5;

template<typename T>

class BlockQueue
{
private:
    bool IsFuLL()
    {
        return _block_queue.size();
    }
public:
    BlockQueue(int cap =):_cap(cap)
    {
        pthread_mutex_init(&_mutex,nullptr);
    }
    void Pop(T *out)
    {

    }
    void Enqueue(const T &in)
    {
        pthread_mutex_t_lock(&_mutex);
        if(IsFuLL())
        {
            //满了生产者不能生产，必须等待！
        }
        pthread_mutex_t_unlock(&_mutex);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
    }
private:
    std::queue<T> _block_queue;         //临界资源
    pthread_mutex_t _mutex;
};
