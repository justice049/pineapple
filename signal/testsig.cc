#include<iostream>
#include<cstdlib>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

int cnt = 1;

void hander(int sig)
{
    std::cout << "get a sig: " << sig << std::endl;
    exit(1);
}

int main()
{
    signal(SIGSEGV,hander);
    // int a = 10;
    // a /= 0;
    int *p = nullptr;
    *p = 100;
    int cnt = 0;
    while (true)
    {
        cnt++;
        std::cout << "hello world" << std::endl;
    }
    
    return 0;
}


// int cnt = 1;

// void hander(int sig)
// {
//     std::cout << "cnt: " << cnt << "get a sig: " << sig << std::endl;
//     exit(1);
// }

// int main()
// {
//     signal(SIGALRM,hander);
//     alarm(1);       
//     while (true)
//     {
//         cnt++;
//     }
//     return 0;
// }



// void hander(int sig)
// {
//     std::cout << "get a sig" << sig <<std::endl;
//     exit(1);
// }

// int main()
// {
//     int cnt = 1;

//     signal(SIGALRM,hander);
//     alarm(1);       //设置一秒后的闹钟
//     while (true)
//     {
//         std::cout << "cnt: " << cnt << std::endl;
//         cnt++;
//     }
//     return 0;
// }


// void hander(int sig)
// {
//     std::cout << "get a sig" << sig <<std::endl;
// }

// int main()
// {
//     int cnt = 0;
//     signal(3,hander);
//     while (true)
//     {
//         sleep(2);
//         abort();
//     }
// }

// //./mykill 2 pid
// int main(int argc,char *argv[])
// {
//     if(argc != 3)
//     {
//         std::cerr << "Usage: " << argv[0] << "signum pid" << std::endl;
//         return 1;
//     }
//     pid_t pid = std::stoi(argv[2]);
//     int signum = std::stoi(argv[1]);

//     kill(pid,signum);
// }

// void hander(int sig)
// {
//     std::cout << "get a sig" << sig <<std::endl;
// }

// int main()
// {
//     signal(2,hander);
//     while (true)
//     {
//         std::cout << "hello world,pid: " << getpid() <<std::endl;
//         sleep(1);
//     }
//     return 0;
// }