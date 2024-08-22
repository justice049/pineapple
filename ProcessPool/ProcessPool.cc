#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"Task.hpp"

// void work(int rfd)
// {
//     while(true)
//     {
//         int command = 0;
//         int n = read(rfd, &command,sizeof(command)); 
//         if(n == sizeof(int))
//         {
//             std::cout << "pid is:" << getpid() << "handler task" << std::endl;
//             ExcuteTask(command);
//         }
//         else if(n == 0)
//         {
//             std::cout<<"Pipe closed"<<std::endl;
//             break;
//         }
//         else
//         {
//             perror("read");
//             break;
//         }
//     }
// }


//master

class Channel
{
public:
    Channel(int wfd, pid_t id, const std::string &name)
    :_wfd(wfd),_subprocessid(id),_name(name)
    {}
    int Getfd()const
    {
        return _wfd;
    }
    pid_t GetProcessId()const
    {
        return _subprocessid;
    }
    std::string GetName()const
    {
        return _name;
    }
    void CloseChannel()
    {
        close(_wfd);
    }
    void Wait()
    {
        pid_t rid = waitpid(_subprocessid,nullptr,0);
        if(rid > 0)
        {
            std::cout << "wait " <<rid << "success" << std::endl;
        }
    }
    ~Channel()
    {

    }
private:
    int _wfd;
    pid_t _subprocessid;
    std::string _name;
};

void CreateChannelAndSub(std::vector<Channel>* channels,int num1,task_t task)
{
    for(int i = 0; i < num1; i++)
    {
        //创建管道
        int pipefd[2] = {0};
        int n = pipe(pipefd);
        if(n < 0)
        {
            perror("pipe");
            exit(1);
        }

        //创建紫禁城
        pid_t id = fork();
        if(id < 0)
        {
            perror("fork");
            exit(1);
        }
        if(id == 0)
        {
            if(!channels->empty())
            {
                //第二次之后创建的管道
                for(auto &channel : *channels)
                {
                    channel.CloseChannel();
                }
            }
            //child
            close(pipefd[1]);
            dup2(pipefd[0],0);
            task();
            close(pipefd[0]);
            exit(0);
        }
       
        //父进程
        close(pipefd[0]);
        //构建名字
        std::string channel_name = "Channel  " + std::to_string(i);
        channels->push_back(Channel(pipefd[1],id,channel_name));
        //close(pipefd[1]);
    }
}

int NextChannel(int channelnum)
{
    static int next = 0;
    int channel = next;
    next++;
    next %= channelnum;
    return channel;
}

void SendTaskCommand(const Channel &channel,int taskcommand)
{
    size_t n = write(channel.Getfd(),&taskcommand,sizeof(taskcommand));
    if(n != sizeof(taskcommand))
    {
        perror("write");
    }
}

void CtrlProcessOnce(std::vector<Channel> &channels)
{
    sleep(1);
    //选择任务
    int taskcommand = Select();
    //选择信道和进程
    int channel_index = NextChannel(channels.size());
    //发送任务
    SendTaskCommand(channels[channel_index],taskcommand);

    std::cout << "taskcommand:" << taskcommand << "  channel:"\
    <<channels[channel_index].GetName() << "  sub process:"\
    << channels[channel_index].GetProcessId() << std::endl;
}

//通过channel来控制紫禁城
void CtrlProcess(std::vector<Channel> &channels,int times = -1)
{
    if(times > 0)
    {
       while(times--)
        {
            CtrlProcessOnce(channels);
        }
    }
    else
    {
        while(true)
        {
            CtrlProcessOnce(channels);
        }
    }
}

//回收管道和子进程
void CleanUpChannels(std::vector<Channel> &channels)
{
    // for(auto &channel : channels)
    // {
    //     channel.CloseChannel();
    // }

    for(auto &channel : channels)
    {
        channel.Wait();
    }
}

// ./processpool 5
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        std::cerr<<"Usage:"<<argv[0]<<"processnum"<<std::endl;
        return 1;
    }
    int num = std::stoi(argv[1]);
    LoadTask();

    std::vector<Channel> channels;
    //创建信道和子进程
    CreateChannelAndSub(&channels,num,work);

    //通过channel控制子进程
    CtrlProcess(channels,10);

    CleanUpChannels(channels);
   
    // for(auto &channel : channels)
    // {
    //     std::cout << " ---------------------- " <<std::endl;
    //     std::cout << channel.GetName() << std::endl;
    //     std::cout << channel.Getfd() << std::endl;
    //     std::cout << channel.GetProcessId() << std::endl;
    // }
    // sleep(100);
    return 0;
}