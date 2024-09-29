#pragma

#include <iostream>

enum
{
    DEBUG = 1,
    INFO,
    WARNING,
    ERRNO,
    FATAL
};

std::string LevelToString(int level)
{
    switch (level)
    {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERRNO:
        return "ERRNO";
    case FATAL:
        return "FATAL";
    default:
        return "UNKNOW";
    }
}

class logmessage
{
public:
    std::string _level;
    pid_t _id;
    int _filename;
    int _filenumber;
    std::string _curr_time;
    std::string _message_info;
};
class Log
{
public:
    Log()
    {

    }
    void LogMessage(std::string filename,int filenumber,int level,const char* format,...)  //介素可变参数
    {
        logmessage lg;
        lg._level = LevelToString(level);
        lg.id = getpid();
    }
    ~Log()
    {

    }
private:
};

int main()
{

    return 0;
}