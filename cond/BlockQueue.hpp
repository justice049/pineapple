#pragma once

#include<iostream>
#include<string>
#include<queue>
#include<pthread.h>
#include<ctime>

const static int defaultcap = 5;        //容量上限

template<typename T>

class BlockQueue
{
private:
    bool IsFuLL()
    {
        return _block_queue.size()==_max_cap;
    }
    bool IsEmpty()
    {
        return _block_queue.empty();
    }
public:
    BlockQueue(int cap = defaultcap):_max_cap(cap)
    {
        srand(time(nullptr));
        pthread_mutex_init(&_mutex,nullptr);
        pthread_cond_init(&_p_cond,nullptr);
        pthread_cond_init(&_c_cond,nullptr);
    }
    void Pop(T *out)
    {
        pthread_mutex_lock(&_mutex);
        while(IsEmpty())        //while可以保证代码的鲁棒性
        {
            pthread_cond_wait(&_c_cond,&_mutex);
        }
        //没有空/被唤醒了
        *out = _block_queue.front();
        _block_queue.pop();
        pthread_mutex_unlock(&_mutex);
        pthread_cond_signal(&_p_cond);      //互相叫醒一下捏
    }
    void Enqueue(const T &in)
    {
        pthread_mutex_lock(&_mutex);
        if(IsFuLL())
        {
            //满了生产者不能生产，必须等待
            pthread_cond_wait(&_p_cond,&_mutex);    //就是我们曾经加的锁
            //在临界区里，不这样会导致死锁
            //pthread_cond_wait被调用的时候，除了让自己继续排队等待，还会自己释放传入的锁
            //函数返回的时候还在临界区
            //返回时必须先参与锁的竞争，重新加锁函数才会返回(这样就是在临界区也持有锁了)
        }
        //没有满/被唤醒了
        _block_queue.push(in);      //将数据生产到阻塞队列
        pthread_mutex_unlock(&_mutex);
        pthread_cond_signal(&_c_cond);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_p_cond);
        pthread_cond_destroy(&_c_cond);         //互相叫醒一下捏
    }
private:
    std::queue<T> _block_queue;         //临界资源
    int _max_cap;
    pthread_mutex_t _mutex;
    pthread_cond_t _p_cond;             //生产者条件变量
    pthread_cond_t _c_cond;             //消费者条件变量
};
