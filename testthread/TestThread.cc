#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *thread1( void *arg )
{
    printf("thread 1 returning ... \n");
    int *p = (int*)malloc(sizeof(int));
    *p = 1;
    return (void*)p;
}
void *thread2( void *arg )
{
    printf("thread 2 exiting ...\n");
    int *p = (int*)malloc(sizeof(int));
    *p = 2;
    pthread_exit((void*)p);
}
void *thread3( void *arg )
{
    while ( 1 )
    { 
        printf("thread 3 is running ...\n");
        sleep(1);
    }
    return NULL;
}
int main( void )
{
    pthread_t tid;
    void *ret;
    // thread 1 return
    pthread_create(&tid, NULL, thread1, NULL);
    pthread_join(tid, &ret);
    printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
    free(ret);
    // thread 2 exit
    pthread_create(&tid, NULL, thread2, NULL);
    pthread_join(tid, &ret);
    printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
    free(ret);

    // thread 3 cancel by other
    pthread_create(&tid, NULL, thread3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &ret);
    if ( ret == PTHREAD_CANCELED )
    {
        printf("thread return, thread id %X, return code:PTHREAD_CANCELED\n", tid);
    }
    else
    {
        printf("thread return, thread id %X, return code:NULL\n", tid);
    }
}




// #include <iostream>
// #include<string>
// #include<cstdio>
// #include<vector>
// #include<pthread.h>
// #include<thread>
// #include<stdlib.h>
// #include <unistd.h>

// std::string ToHex(pthread_t tid)
// {
//     char id[128];
//     snprintf(id,sizeof(id),"0x%x",tid);
//     return id;
// }

// void* threadRun(void *args)
// {
//     std::string name = static_cast<const char*>(args);
//     while (true)
//     {
//         std::cout << name << " is running,tid: " << ToHex(pthread_self()) << std::endl;
//         sleep(1);
//     }
    
// }

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid,nullptr,threadRun,(void*)"thread-1");

//     std::cout << "new thread tid: " << ToHex(tid) << std::endl;

//     pthread_join(tid,nullptr);
//     return 0;
// }

// void threadRun(std::string name,int num)
// {
//     while (num)
//     {
//         std::cout << name << " num: " << num << std::endl;
//         num--;
//         sleep(1);
//     }
    
// }

// int main()
// {
//     std::string name = "thread-1";
//     std::thread mythread(threadRun, name ,10);
//     while (true)
//     {
//         std::cout << "main thread..." << std::endl;
//     }
    
//     mythread.join();
//     return 0;
// }
