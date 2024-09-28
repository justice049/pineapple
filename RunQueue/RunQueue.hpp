#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<pthread.h>
#include<semaphore.h>

template<typename T>
class RingQueue
{
private:
    void P(sem_t &s)
    {
        sem_wait(&s);
    }
    void V(sem_t &s)
    {
        sem_post(&s);
    }
public:
    RingQueue(int max_cap)
    :_max_cpp(max_cap),_ringqueue(max_cap),_c_step(0),_p_step(0)
    {
        sem_init(&_data_sem,0,0);
        sem_init(&_space_sem,0,max_cap);

        pthread_mutex_init(&_c_mutex,nullptr);
        pthread_mutex_init(&_p_mutex,nullptr);
    }
    void Push(const T &in)      //生产者
    {
        P(_space_sem);
        pthread_mutex_lock(&_p_mutex);          //加锁
        _ringqueue[_p_step]=in;
        _p_step++;
        _p_step%=_max_cpp;      //因为是环形队列
        V(_data_sem);           //完成生产要释放资源
        pthread_mutex_unlock(&_p_mutex);    //解锁
    }
    void Pop(T* out)            //消费者
    {
        P(_data_sem);
        pthread_mutex_lock(&_c_mutex);          //加锁
        *out = _ringqueue[_c_step];
        _c_step++;
        _c_step%=_max_cpp;
        V(_space_sem);
        pthread_mutex_unlock(&_c_mutex);        //解锁
    }
    ~RingQueue()
    {
        sem_destroy(&_data_sem);
        sem_destroy(&_space_sem);

        pthread_mutex_destroy(&_c_mutex);
        pthread_mutex_destroy(&_p_mutex);
    }
private:
    std::vector<T> _ringqueue;
    int _max_cpp;

    int _c_step;
    int _p_step;

    sem_t _data_sem;        //消费者关心
    sem_t _space_sem;       //生产者关心

    pthread_mutex_t _c_mutex;
    pthread_mutex_t _p_mutex;
};
