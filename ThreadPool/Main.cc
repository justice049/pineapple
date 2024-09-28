#include"ThreadPool.hpp"

int main()
{
    //std::unique_ptr<ThreadPool> tp = std::make_unique<ThreadPool>();
    ThreadPool<int> *tp = new ThreadPool<int>();
    tp->Init();
    tp->Start();
    while (true)
    {
        //不断向线程池中推送任务
        
    }
    
    return 0;
}