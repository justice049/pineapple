#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>

void notice(int signo)
{
    std::cout << "get a signal: " << signo << "pid:" << getpid() << std::endl;
    pid_t rid = waitpid(-1,nullptr,0);
    if(rid > 0)
    {
        std::cout << "wait child success ,rid: " << rid << std::endl;
    }
}

int main()
{
    signal(SIGCHLD,notice);
    pid_t id = fork();
    if(id == 0)
    {
        std::cout << "I am child process" << std::endl;
        sleep(3);
        exit(1);
    }

    //father
    sleep(100);
    return 0;
}

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