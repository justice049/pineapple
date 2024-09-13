#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/wait.h>

void PrintPending(sigset_t &pending)
{
    std::cout << "current process[" << getpid() << "]" << " pending: ";
    for(int signo = 31; signo >=1;signo--)
    {
        if(sigismember(&pending, signo))
        {
            //判定signo是否在集合里
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }
    std::cout << "\n";
}

void handler(int signo)
{
    std::cout << signo << "号信号被递达" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    sigset_t pending;
    sigpending(&pending);
    PrintPending(pending);
    std::cout << "--------------------------------" << std::endl;
}

int main()
{
    //捕捉2号信号
    signal(2,handler);
    //屏蔽2号信号
    sigset_t block_set,old_set;
    sigemptyset(&block_set);
    sigemptyset(&old_set);
    sigaddset(&block_set,SIGINT);   //还没修改内核block表
    
    //设置进入进程的block中
    sigprocmask(SIG_BLOCK,&block_set,&old_set);     //修改当前内核的block表，对2号信号进行屏蔽

    int cnt = 10;
    while (true)
    {
        //获取当前进程的pending信号集
        sigset_t pending;
        sigpending(&pending);

        //打印pending信号类
        PrintPending(pending);
        sleep(1);

        //解除对2号信号的屏蔽
        cnt--;
        if(cnt == 0)
        {
            std::cout << "解除对2号信号的屏蔽" << std::endl;
            sigprocmask(SIG_SETMASK, &old_set, &block_set);
        }
    }
    
    return 0;
}




// int main()
// {
//     sigset_t bits;     //sigset_t是Linux给用户提供的一个用户级数据类型，禁止用户直接

//     return 0;
// }


// struct bits
// {
//     uint32_t bits[400];     //400*32毕竟是位图
// };

// //位图原理
// //40    //我们假设得出的结果是40
// //40/(sizeof(uint32_t)*8) = 1 -> bits[1]
// //40%(sizeof(uint32_t)*8) = 8 -> bits[1]:8   //第八个比特位

// int main()
// {
//     return 0;
// }

// int Sum(int start,int end)
// {
//     int sum = 0;
//     for(int i = start; i <= end; i++)
//     {
//         sum/=0;     //core
//         sum+=i;
//     }
// }

// int main()
// {
//     // int total = Sum(0,100);
//     // std::cout << "total: " << total << std::endl;
//     pid_t id = fork();
//     if(id == 0)
//     {
//         sleep(1);
//         //child
//         Sum(0,100);
//         exit(0);
//     }

//     //father
//     int status = 0;
//     pid_t rid = waitpid(id,&status,0);
//     if(rid == id)
//     {
//         printf("exit code:%d,exit sig: %d,core dump: %d\n",(status>>8)&0xFF,status&0x7F,(status>>7)&0x1);
//     }
//     return 0;
// }