#pragma once
#include<iostream>
#include<functional>
#include<string>
#include<pthread.h>

namespace ThreadMoudle
{
    //线程要执行的方法
    //using func_t = std::function<void()>;
    typedef void(*func_t)(const std::string &name);        //函数指针类型
    class Thread
    {
    public:
        void Excute()
        {
            _isrunning = true;
            _func(_name);
        }
    public:
        Thread(const std::string &name,func_t func):_name(name),_func(func)
        {
            
        }
        static void *ThreadRoutine(void* args)     //新线程执行的方法
        {
            Thread *self = static_cast<Thread*>(args);      //获得当前对象
            self->Excute();
        }
        bool Start()
        {
            int n = ::pthread_create(&_tid,nullptr,ThreadRoutine,this);      //这个::指用系统提供的
            if(n != 0)
            {
                return false;
            }
            return true;
        }
        std::string Status()            //线程启动检测下状态
        {
            if(_isrunning)
            {
                return "running";
            }
            return "sleep";
        }
        void Stop()
        {
            if(_isrunning)
            {
                pthread_cancel(_tid);
                _isrunning = false;
            }
        }
        void Join()
        {
            if(!_isrunning)
            {
                pthread_join(_tid,nullptr);
            }
            std::cout << "join done" << std::endl;
        }
        std::string Name()
        {
            return _name;
        }
        ~Thread()
        {
            Stop();
            Join();
        }
    private:
        std::string _name;
        pthread_t _tid;
        bool _isrunning;
        func_t _func;    //线程要执行的回调函数

        //std::string _result;        //返回值，不关心的话也可以不用写
    };  
}
