#include<iostream>
#include<string>
#include<unistd.h>
#include<pthread.h>

const int num = 5;
pthread_mutex_t gmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t gcond = PTHREAD_COND_INITIALIZER;    //条件变量的初始化

void* Wait(void* args)
{
    std::string name = static_cast<const char*>(args);
    while (true)
    {
        pthread_mutex_lock(&gmutex);

        pthread_cond_wait(&gcond,&gmutex);  
        std::cout << "I am:" << name << std::endl;
        
        pthread_mutex_unlock(&gmutex);
        sleep(1); 
    }
}

int main()
{
    pthread_t threads[num];
    for(int i=0;i<num;i++)
    {
        char *buffer=new char[1024];
        snprintf(buffer,1024,"thread-%d",i + 1);
        pthread_create(threads+i,nullptr,Wait,(void*)buffer);
    }

    //唤醒这个线程
    while (true)
    {
        //pthread_cond_signal(&gcond);
        pthread_cond_broadcast(&gcond);         //指定条件变量全唤醒
        std::cout << "唤醒一个线程..." << std::endl;
        sleep(2);
    }
    
    for(int i=0;i<num;i++)
    {
        pthread_join(threads[i],nullptr);
    }
    return 0;
}