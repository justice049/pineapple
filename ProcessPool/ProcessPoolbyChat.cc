#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Task.hpp"
 
// Ensure proper function declarations
void LoadTask();
int Select();
void ExcuteTask(int command);
 
void work(int rfd)
{
    while (true)
    {
        int command = 0;
        ssize_t n = read(rfd, &command, sizeof(command)); 
        if (n == sizeof(int))
        {
            std::cout << "pid is: " << getpid() << " handling task" << std::endl;
            ExcuteTask(command);
        }
        else if (n == 0)
        {
            // Pipe closed; exit the loop if there's no more data
            break;
        }
        else
        {
            perror("read");
            break;
        }
    }
}
 
class Channel
{
public:
    Channel(int wfd, pid_t id, const std::string &name)
    : _wfd(wfd), _subprocessid(id), _name(name)
    {}
 
    int Getfd() const
    {
        return _wfd;
    }
 
    pid_t GetProcessId() const
    {
        return _subprocessid;
    }
 
    std::string GetName() const
    {
        return _name;
    }
 
    ~Channel()
    {
        close(_wfd); // Close file descriptor in the destructor
    }
 
private:
    int _wfd;
    pid_t _subprocessid;
    std::string _name;
};
 
void CreateChannelAndSub(std::vector<Channel>* channels, int num1)
{
    for (int i = 0; i < num1; i++)
    {
        int pipefd[2] = {0};
        int n = pipe(pipefd);
        if (n < 0)
        {
            perror("pipe");
            exit(1);
        }
 
        pid_t id = fork();
        if (id < 0)
        {
            perror("fork");
            exit(1);
        }
        if (id == 0)
        {
            close(pipefd[1]);
            work(pipefd[0]);
            close(pipefd[0]);
            exit(0);
        }
 
        close(pipefd[0]);
        std::string channel_name = "Channel " + std::to_string(i);
        channels->emplace_back(pipefd[1], id, channel_name);
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
 
void SendTaskCommand(const Channel &channel, int taskcommand)
{
    ssize_t n = write(channel.Getfd(), &taskcommand, sizeof(taskcommand));
    if (n != sizeof(taskcommand))
    {
        perror("write");
    }
}
 
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " processnum" << std::endl;
        return 1;
    }
    int num = std::stoi(argv[1]);
    LoadTask();
 
    std::vector<Channel> channels;
    CreateChannelAndSub(&channels, num);
 
    int numSize = 5;
    while (numSize--)
    {
        int taskcommand = Select();
        int channel_index = NextChannel(channels.size());
        SendTaskCommand(channels[channel_index], taskcommand);
 
        std::cout << "taskcommand: " << taskcommand 
                  << " channel: " << channels[channel_index].GetName() 
                  << " sub process: " << channels[channel_index].GetProcessId() 
                  << std::endl;
    }
 
    // Wait for all child processes to terminate
    for (auto &channel : channels)
    {
        int status;
        waitpid(channel.GetProcessId(), &status, 0);
    }
 
    return 0;
}