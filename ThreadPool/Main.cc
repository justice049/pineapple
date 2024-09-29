#include"ThreadPool.hpp"
#include"Task.hpp"

int main()
{
    //std::unique_ptr<ThreadPool> tp = std::make_unique<ThreadPool>();
    ThreadPool<Task> *tp = new ThreadPool<Task>();
    tp->Init();
    tp->Start();
    while (true)
    {
        //不断向线程池中推送任务
        sleep(1);
        Task t(1,1);
        tp->Enqueue(t);
        sleep(1);
    }
    tp->Stop();
    std::cout << "thread pool stop" << std::endl;
    sleep(10);
    return 0;
}