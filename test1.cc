#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    signal(SIGCHLD, SIG_IGN);       //收到设置对SIGCHLD进行忽略
    pid_t id = fork();
    if(id == 0)
    {
        int cnt = 5;
        while (cnt)
        {
            std::cout << "chlid running" << std::endl;
            cnt--;
            sleep(1);
        }
        exit(1);
    }
    //father
    while (true)
    {
        std::cout << "chlid running" << std::endl;
        sleep(1);
    }
    exit(1);
    return 0;
}







// void notice(int signo)
// {
//     std::cout << "get a signal: " << signo << "pid:" << getpid() << std::endl;
//     while (true)
//     {
//         pid_t rid = waitpid(-1, nullptr, WNOHANG);      //非阻塞方式
//         if (rid > 0)
//         {
//             std::cout << "wait child success ,rid: " << rid << std::endl;
//         }
//         else if(rid < 0)
//         {
//             std::cout << "wait child success done " << std::endl;
//             break;
//         }
//         else
//         {
//             std::cout << "wait child success done " << std::endl;
//             break;
//         }
//     }
// }

// int main()
// {
//     signal(SIGCHLD, notice);
//     pid_t id = fork();
//     if (id == 0)
//     {
//         std::cout << "I am child process" << std::endl;
//         sleep(3);
//         exit(1);
//     }

//     // father
//     sleep(100);
//     return 0;
// }

// volatile int gflag = 0;

// void changedata(int signo)
// {
//     std::cout << "get a signo:" << signo << ",change gflag 0 -> 1" << std::endl;
//     gflag = 1;
// }

// int main()
// {
//     signal(2,changedata);
//     while (!gflag);
//     std::cout << "process quit normal" << std::endl;

// }