#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int pipefd[2]={0};
    if(pipe(pipefd)!=0)
    {
        perror("pipe error");
        return 1;
    }
    printf("fd1==%d\nfd2==%d\n",pipefd[0],pipefd[1]);
    if(fork()==0)
    {
        //子进程部分
        close(pipefd[0]);//关掉读
        const char* msg="hello linux";
        while(1)
        {
             write(pipefd[1],msg,strlen(msg));
             sleep(1);
        }
        exit(0);
    }
    close(pipefd[1]);//父进程部分，关掉写方法
    while(1)
    {
        char buffer[64]={0};
        ssize_t s=read(pipefd[0],buffer,sizeof(buffer));
        if(s<=0)
        {
            break;
        }
        else if(s>0)
        {
            buffer[s]=0;
            printf("child say to father:%s\n",buffer);
        }
     }
    return 0; 
}