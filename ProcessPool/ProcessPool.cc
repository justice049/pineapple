#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/types.h>

void work(int rfd)
{
    while(true)
    {
        sleep(1);
    }
}

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
    ~Channel()
    {

    }
private:
    int _wfd;
    pid_t _subprocessid;
    std::string _name;
};

void CreateChannelAndSub(std::vector<Channel>* channels,int num1)
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
            //child
            close(pipefd[1]);
            work(pipefd[0]);
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

// ./processpool 5
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        std::cerr<<"Usage:"<<argv[0]<<"processnum"<<std::endl;
        return 1;
    }
    int num = std::stoi(argv[1]);

    std::vector<Channel> channels;
    //创建信道和子进程
    CreateChannelAndSub(&channels,num);

    

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