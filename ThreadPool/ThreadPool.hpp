#pragma once

#include<iostream>
#include<unistd.h>
#include<string>
#include<vector>
#include<queue>
#include"Thread.hpp"

using namespace ThreadMoudle;

static const int gdefaultnum = 5; 

template<typename T>
class ThreadPool
{
public:
    ThreadPool(int thraed_num = gdefaultnum):_thread_num(thraed_num),_isrunning(false)
    {

    }
    void Init()
    {
        
    }
    void Start()
    {

    }
    void Stop()
    {

    }
    void Enqueue(const T &in)
    {

    }
    ~ThreadPool()
    {

    }
private:
    int _thread_num;
    std::vector<Thread> _threads;
    std::queue<T> _task_queue;
    bool _isrunning;
};

