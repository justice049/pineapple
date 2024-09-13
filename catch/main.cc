#include<iostream>
#include<signal.h>

void Print(sigset_t &pending)
{
    for(int sig = 31;sig > 0; sig--)
    {
        if(sigismember(&pending, sig))
        {
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }
    std::cout << std::endl;
}

//当前如果正在对2号信号进程处理，默认2号信号会被自动屏蔽
//对2号信号处理完成的时候，会自动解除对2号信号的屏蔽

void handler(int signum)
{
    std::cout << "get a sig" << signum << std::endl;
    while (true)
    {
        sigset_t pending;
        sigpending(&pending);

        Print(pending);
        sleep(1);
    }
    exit(1);
}


int main()
{
    struct sigaction act,oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
    //进行自定义捕捉
    sigaction(2,&act,&oact);

    while (true)
    {
        std::cout << "I am a process,pid: " << getpid() << std::endl;
        sleep(1);
    }
    
    return 0;
}