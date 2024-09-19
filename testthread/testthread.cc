#include <iostream>
#include<string>
#include<vector>
#include<pthread.h>
#include <unistd.h>
#include <ctime>

void* threadrun(void* args)
{
    pthread_detach(pthread_self());         //这个相当于get线程的id
    std::string name = static_cast<const char*>(args);
    while (true)
    {
        std::cout << name << " is running" << std::endl;
        sleep(1);
        break;
    }
    pthread_exit(args);         //专门终止线程
}

const int num = 10;

int main()
{
    std::vector<pthread_t>tids;
    for(int i=0;i<num;i++)
    {
        //有线程的ID
        pthread_t tid;
        char *name = new char[128];
        snprintf(name,128,"thread-%d",i+1);

        pthread_create(&tid,nullptr,threadrun,name);
        tids.push_back(tid);
    }

    for(auto tid : tids)
    {
        void *name = nullptr;
        pthread_join(tid,&name);
        std::cout << (const char*)name << " quit... " << std::endl;
        delete (const char*)name;
    }
    return 0;
}

// int main()
// {
//     std::vector<pthread_t>tids;
//     for(int i=0;i<num;i++)
//     {
//         //有线程的ID
//         pthread_t tid;
//         char *name = new char[128];
//         snprintf(name,128,"thread-%d",i+1);

//         pthread_create(&tid,nullptr,threadrun,name);
//         tids.push_back(tid);
//     }

//     for(auto tid : tids)
//     {
//         void *name = nullptr;
//         pthread_join(tid,&name);
//         std::cout << (const char*)name << " quit... " << std::endl;
//         delete (const char*)name;
//     }
//     return 0;
// }

// class ThreadData
// {
// public:
//     std::string name;
//     std::string num;
// };

// void* threadRun(void* args)
// {
//     int cnt = 5;
//     ThreadData *td = static_cast<ThreadData*>(args);
//     while (cnt)
//     {
//         std::cout << "new thread run ...,cnt : " << cnt-- << std::endl;
//         sleep(1);
//     }
//     return nullptr;    
// }



// int main()
// {

//     // pthread_t tid;      //线程的ID
//     // ThreadData *td = new ThreadData();
//     // td->name = "thread-1";
//     // td->num = 1;
//     // int n = pthread_create(&tid,nullptr,threadRun,td);
//     // if(n != 0)
//     // {
//     //     std::cerr << "create thread error" << std::endl;
//     //     return 1;
//     // }
//     // void *code = nullptr;           //开辟了空间
//     // n = pthread_join(tid,&code);

//     // std::cout << "main thread join begin..." << std::endl;
//     // if(n == 0)
//     // {
//     //     std::cout << "main thread wait success" << std::endl;
//     // }
//     return 0;
// }


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