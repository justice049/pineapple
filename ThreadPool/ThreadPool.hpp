#pragma once

#include"Log.hpp"
#include <iostream>
#include <unistd.h>
#include <functional>
#include <string>
#include <vector>
#include <pthread.h>
#include <queue>
#include "Thread.hpp"

Log lg;

#define LOG(Level, Format, ...) do { \
    lg.LogMessage(__FILE__, __LINE__, Level, Format, ##__VA_ARGS__); \
} while(0)

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

template <typename T>
class ThreadPool
{
private:
    void LockQueue()
    {
        pthread_mutex_lock(&_mutex);
    }
    void UnLockQueue()
    {
        pthread_mutex_unlock(&_mutex);
    }
    void WakeUp()
    {
        pthread_cond_signal(&_cond);
    }
    void WakeUpAll()
    {
        pthread_cond_broadcast(&_cond);
    }
    void Sleep()
    {
        pthread_cond_wait(&_cond, &_mutex);
    }
    bool IsEmpty()
    {
        return _task_queue.empty();
    }
    void HandlerTask()
    {
        while (true)
        {
            LockQueue();
            while (IsEmpty() && _isrunning) // 为了防止伪唤醒的情况发生
            {
                _sleep_thread_num++; // 保证加锁和解锁都安全更新
                Sleep();
                _sleep_thread_num--;
            }
            // 判定一种情况
            if (IsEmpty() && !_isrunning) // 空了并且退出那就退罢
            {
                std::cout << "quit" << std::endl;
                UnLockQueue();
                break;
            }
            // 有任务
            T t = _task_queue.front(); // 取出
            _task_queue.pop();         // 老的弹出去
            UnLockQueue();

            t(); // 处理任务，不能在临界区处理
            std::cout << t.debug() << std::endl;
        }
    }

    ThreadPool(int thread_num = gdefaultnum) : _thread_num(thread_num), _isrunning(false), _sleep_thread_num(0)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    ThreadPool(const ThreadPool<T> &) = delete;         //赫赫这就是我们单例模式
    void operator = (const ThreadPool<T> &) = delete;
public:
    void Init()
    {
        func_t func = std::bind(&ThreadPool::HandlerTask, this); // 让this和handlertask强关联起来，能让一个模块调用另一个类中的方法
        for (int i = 0; i < _thread_num; i++)
        {
            std::string threadname = "thread-" + std::to_string(i + 1);
            _threads.emplace_back(threadname, func);
        }
    }
    void Start()
    {
        _isrunning = true;
        for (auto &thread : _threads)
        {
            thread.Start();
        }
    }
    void Stop()
    {
        LockQueue();
        _isrunning = false;
        WakeUpAll();
        UnLockQueue();
    }
    static ThreadPool<T> *GetInstance()
    {
        if(_tp==nullptr)
        {
            LOG(INFO,"create threadpool\n");
            _tp=new ThreadPool();
            _tp->Init();
            _tp->Start();
        }
        else
        {
            LOG(INFO,"get threadpool\n");
        }
        return _tp;
    }
    void Enqueue(const T &in)
    {
        LockQueue(); // 加锁
        if (_isrunning)
        {
            _task_queue.push(in);

            if (_sleep_thread_num > 0)
            {
                WakeUp();
            }
        }
        UnLockQueue(); // 解锁
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

    int _sleep_thread_num; // 我们定义一个计数器来确定什么时候唤醒它

    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    //单例模式
    static ThreadPool<T> *_tp;
    
};

//静态指针的初始化需要在类外
template<typename T>
ThreadPool<T> *ThreadPool<T>::_tp = nullptr;