#include <iostream>
#include <unistd.h>
#include <ctime>

int gval = 100;

// 新线程
void *threadStart(void *args)
{
    while (true)
    {
        sleep(1);
        std::cout << "new thread running..." << ",pid: " << getpid() << " gval: " << gval << " &gval: " << &gval << std::endl;

        // int x = rand()%50;
        // if(x == 0)
        // {
        //     int *p = nullptr;
        //     *p = 100;       //野指针
        // }
    }
}

int main()
{
    srand(time(nullptr));

    pthread_t tid1;
    pthread_create(&tid1, nullptr, threadStart, (void *)"thread-new");

    pthread_t tid2;
    pthread_create(&tid2, nullptr, threadStart, (void *)"thread-new");

    pthread_t tid3;
    pthread_create(&tid3, nullptr, threadStart, (void *)"thread-new");

    // 主线程
    while (true)
    {
        sleep(1);
        std::cout << "main thread running..." << ",pid: " << getpid() << std::endl;
        std::cout << "new thread running..." << ",pid: " << getpid() << " gval: " << gval << " &gval: " << &gval << std::endl;
        gval++;             //修改
    }
    return 0;
}