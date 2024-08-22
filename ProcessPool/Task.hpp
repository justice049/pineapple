#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>

#define TaskNum 3

typedef void(*task_t)();  //函数指针

task_t tasks[TaskNum];

void work()
{
    while(true)
    {
        int command = 0;
        int n = read(0, &command,sizeof(command)); 
        if(n == sizeof(int))
        {
            std::cout << "pid is:" << getpid() << "handler task" << std::endl;
            ExcuteTask(command);
        }
        else if(n == 0)
        {
            std::cout<<"Pipe closed"<<std::endl;
            break;
        }
        else
        {
            perror("read");
            break;
        }
    }
}

void Print()
{
    std::cout<<"pineapple"<<std::endl;
}

void Download()
{
    std::cout<<"Download Task"<<std::endl;
}

void Flush()
{
    std::cout<<"Flush Task"<<std::endl;
}

void LoadTask()
{
    srand(time(nullptr) ^ getpid() ^ 114514);   //没别的意思我随便写的
    tasks[0]= Print;
    tasks[1]=Download;
    tasks[2]=Flush;
}

void ExcuteTask(int number)
{
    if(number<0 || number>2)
    {
        return; 
    }
    tasks[number]();
}

int Select()
{
    return rand() % TaskNum;
}