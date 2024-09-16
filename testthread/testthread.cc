#include <iostream>
#include <unistd.h>

// 新线程
void *threadStart(void *args)
{
    while (true)
    {
        sleep(1);
        std::cout << "new thread running..." << ",pid: " << getpid() << std::endl;
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadStart, (void *)"thread-new");

    // 主线程
    while (true)
    {
        sleep(1);
        std::cout << "main thread running..." << ",pid: " << getpid() << std::endl;
    }
    return 0;
}