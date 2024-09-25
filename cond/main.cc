#include"BlockQueue.hpp"
#include<pthread.h>
#include<ctime>
#include<unistd.h>

void* Consumer(void* args)
{
    BlockQueue<int> *bq = static_cast<BlockQueue<int>*>(args);
    while (true)
    {
        sleep(1);
        //获取数据
        int data = 0;
        bq->Pop(&data);
        //处理数据
        std::cout << "Consumer -> " << data << std::endl;
    }
    
}

void *Productor(void* args)
{
    srand(time(nullptr)^getpid());
    BlockQueue<int> *bq = static_cast<BlockQueue<int>*>(args);
    while(true)
    {
        //构建数据
        int data = rand()%10+1;     //[1,10]
        //生产数据
        bq->Enqueue(data);
        std::cout << "Productor -> " << data << std::endl;
    }
}

int main()
{
    BlockQueue<int> *bq = new BlockQueue<int>();
    pthread_t c,p;      //生产者消费者
    pthread_create(&c,nullptr,Consumer,bq);
    pthread_create(&p,nullptr,Productor,bq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    return 0;
}