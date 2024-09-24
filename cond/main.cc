#include"BlockQueue.hpp"
#include<pthread.h>

void* Consumer(void* args)
{
    BlockQueue *bq = static_cast<BlockQueue *>(args);
    while (true)
    {
        //获取数据
        bq->Pop();
        //处理数据
    }
    
}

void *Productor(void* args)
{
    BlockQueue *bq = static_cast<BlockQueue *>(args);
    while(true)
    {
        //构建数据
        //生产数据
        
    }
}

int main()
{
    BlockQueue *bq = new BlockQueue();
    pthread_t c,p;      //生产者消费者
    pthread_create(&c,nullptr,Consumer,bq);
    pthread_create(&p,nullptr,Productor,bq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}