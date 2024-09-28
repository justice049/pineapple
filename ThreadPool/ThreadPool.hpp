#pragma once

#include<iostream>
#include<unistd.h>
#include<string>
#include<vector>
#include<queue>
#include"Thread.hpp"

using namespace ThreadMoudle;

static const int gdefaultnum = 5;

void test()
{
    while (true)
    {
        std::cout << "hello EPI?" << std::endl;
        sleep(1); 
    }
}

template<typename T>
class ThreadPool
{
private:
    void LockQueue()
    {
        pthraed_mutex_lock(&_mutex);
    }
    void UnLockQueue()
    {
        pthread_mutex_unlock(&_mutex);
    }
    void WakeUp()
    {
        pthread_cond_signal(&_cond);
    }
    void Sleep()
    {
        
    }
    void IsEmpty()
    {
        return _task_queue.empty();
    }
    void HandlerTask()
    {
        while (true)
        {
            LockQueue();
            if(IsEmpty())
            {

            }
            UnLockQueue();
        }
        
    }
public:
    ThreadPool(int thraed_num = gdefaultnum):_thread_num(thraed_num),_isrunning(false),_sleep_thread_num(0)
    {
        pthread_mutex_init(&_mutex);
        pthread_cond_init(&_cond);
    }
    void Init()
    {
        for(int i=0;i<_thread_num;i++)
        {
            std::string threadname = "thread-" + std::to_string(i+1);
            _threads.emplace_back(threadname,test);
        }
    }
    void Start()
    {
        for(auto &thread:_threads)
        {
            thread.Start();
        }
    }
    void Stop()
    {

    }
    void Enqueue(const T &in)
    {
        LockQueue();        //加锁
        _task_queue.push(in);
        if(_sleep_thread_num > 0)
        {
            WakeUp();
        }
        UnLockQueue();      //解锁
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
private:
    int _thread_num;
    std::vector<Thread> _threads;
    std::queue<T> _task_queue;
    bool _isrunning;

    int _sleep_thread_num;      //我们定义一个计数器来确定什么时候唤醒它

    pthread_mutex_t _mutex;
    pthread_mutex_t _cond;
};

