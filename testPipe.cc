#include<iostream>
#include<cerrno>
#include<cstring>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/wait.h>

const int size = 1024;

std::string getOtherMessage()
{
    static int cnt =0;
    std::string messageid=std::to_string(cnt);
    cnt++;
    pid_t self_id=getpid();
    std::string stringpid=std::to_string(self_id);

    std::string message="messageid: ";
    message+=messageid;
    message+="    my pid is: ";
    message+=stringpid;

    return message;
}

//子进程写入
void SubProcessWrite(int wfd)
{
    std::string message = "father, I am your son process!   ";
    while (true)
    {
        std::string info = message + getOtherMessage();
        write(wfd,info.c_str(),info.size());
        sleep(1);
    }
}

//父进程读取
void FatherProcessRead(int rfd)
{
    char inbuffer[size];     //c99  gnu  g99     
    while(true)
    {
        ssize_t n =read(rfd,inbuffer,sizeof(inbuffer)-1);
        if(n>0)
        {
            inbuffer[n] = 0;     //你不带上无所谓，我会自己添加
            std::cout << "father get message:" << inbuffer << std::endl;
        }
    }
}

int main()
{
    //创建管道
    int pipefd[2];
    int n= pipe(pipefd);   //输出型参数，rfd,wfd
    if(n!=0)
    {
        std::cerr<<"errno:"<<errno<<":"<<"errstring:"<<strerror(errno)<<std::endl;
        return 1;
    }
    std::cout<<"piped[0]:"<<pipefd[0]<<"pipefd[1]:"<<pipefd[1]<<std::endl;

    //创建子进程
    pid_t id=fork();
    if(id==0)
    {
        std::cout << "我是儿子，我准备好了，我准备好了！" << std::endl;
        //关闭不需要的fd
        close(pipefd[0]);
        //子进程 -- write
        if(fork()>0)
        {
            exit(0);
        }
        SubProcessWrite(pipefd[1]);   
        close(pipefd[1]);
        exit(0);
    }
    close(pipefd[1]);
    //父进程 -- read
    std::cout << "我是爹，我准备好了，我准备好了！" << std::endl;
    FatherProcessRead(pipefd[0]);
    close(pipefd[0]);

    pid_t rid=waitpid(id,nullptr,0);
    if(rid>0)
    {
        std::cout<<"wait child process done"<<std::endl;
    }
    return 0;
}