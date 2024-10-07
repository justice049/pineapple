#include"ThreadPool.hpp"
#include"Task.hpp"
#include"Log.hpp"

int main()
{
    Log::FlushLogToScreen();
    int cnt = 10;
    while (cnt)
    {
        sleep(1);
        Task t(1,1);
        ThreadPool<Task>::GetInstance()->Enqueue(t);
        LOG(INFO,"enqueue a task,%s\n",t.debug().c_str());
        sleep(1);
        cnt--;
    }
    ThreadPool<Task>::GetInstance()->Stop();
    LOG(INFO,"thraed pool stop!\n");
    return 0;
}

// int main()
// {
//     // Log lg;
//     // lg.Enable(FILE_TYPE);
//     LOG(DEBUG,"hello %d,world: %c,hello: %f\n",1000,'A',3.14);
//     sleep(1);
//     return 0;
// }

// int main()
// {
//     //std::unique_ptr<ThreadPool> tp = std::make_unique<ThreadPool>();
//     ThreadPool<Task> *tp = new ThreadPool<Task>();
//     tp->Init();
//     tp->Start();
//     while (true)
//     {
//         //不断向线程池中推送任务
//         sleep(1);
//         Task t(1,1);
//         tp->Enqueue(t);
//         sleep(1);
//     }
//     tp->Stop();
//     std::cout << "thread pool stop" << std::endl;
//     sleep(10);
//     return 0;
// }