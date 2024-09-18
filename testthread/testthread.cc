#include <iostream>
#include<string>
#include<pthread.h>
#include <unistd.h>
#include <ctime>

void* threadRun(void* args)
{
    int cnt = 5;
    while (cnt)
    {
        std::cout << "new thread run ...,cnt : " << cnt-- << std::endl;
        sleep(1);
    }
    return nullptr;    
}

int main()
{
    pthread_t tid;      //线程的ID
    int n = pthread_create(&tid,nullptr,threadRun,(void*)"thread 1");
    if(n != 0)
    {
        std::cerr << "create thread error" << std::endl;
        return 1;
    }
    n = pthread_join(tid,nullptr);
    std::cout << "main thread join begin..." << std::endl;
    if(n == 0)
    {
        std::cout << "main thread wait success" << std::endl;
    }
    return 0;
}


//int gval = 100;


// // 新线程
// void *threadStart(void *args)
// {
//     while (true)
//     {
//         sleep(1);
//         std::cout << "new thread running..." << ",pid: " << getpid() << " gval: " << gval << " &gval: " << &gval << std::endl;

//         // int x = rand()%50;
//         // if(x == 0)
//         // {
//         //     int *p = nullptr;
//         //     *p = 100;       //野指针
//         // }
//     }
// }

// int main()
// {
//     srand(time(nullptr));

//     pthread_t tid1;
//     pthread_create(&tid1, nullptr, threadStart, (void *)"thread-new");

//     pthread_t tid2;
//     pthread_create(&tid2, nullptr, threadStart, (void *)"thread-new");

//     pthread_t tid3;
//     pthread_create(&tid3, nullptr, threadStart, (void *)"thread-new");

//     // 主线程
//     while (true)
//     {
//         sleep(1);
//         std::cout << "main thread running..." << ",pid: " << getpid() << std::endl;
//         std::cout << "new thread running..." << ",pid: " << getpid() << " gval: " << gval << " &gval: " << &gval << std::endl;
//         gval++;             //修改
//     }
//     return 0;
// }