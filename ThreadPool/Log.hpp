#pragma

#include <iostream>
#include<unistd.h>
#include<sys/types.h>
#include<ctime>
#include<stdarg.h>

#define SCREEN_TYPE 1
#define FILE_TYPE 2

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

std::string GetCurTime()
{
    time_t now = time(nullptr);
    struct tm *curr_time = localtime(&now);
    char buffer[128];
    snprintf(buffer,sizeof(buffer),"%d-%02d-%02d : %02d-%02d-%02d",\
    curr_time->tm_year+1900,\
    curr_time->tm_mon+1,\
    curr_time->tm_mday,\
    curr_time->tm_hour,\
    curr_time->tm_min,\
    curr_time->tm_sec);
    return buffer;
}

class logmessage
{
public:
    std::string _level;
    pid_t _id;
    std::string _filename;
    int _filenumber;
    std::string _curr_time;
    std::string _message_info;
};
class Log
{
public:
    Log(const std::string &logfile):_logfile(logfile),_type(SCREEN_TYPE)
    {

    }
    Log():_type(SCREEN_TYPE)
    {

    }
    void Enable(int type)
    {
        _type = type;
    }
    void FlushLogToScreen(const logmessage &lg)
    {
        printf("[%s][%d][%s][%d][%s] %s",
            lg._level.c_str(),
            lg._id,
            lg._filename.c_str(),
            lg._filenumber,
            lg._curr_time,
            lg._message_info
            );
    }
    void FlushLogToFile(const logmessage &lg)
    {

    }
    void FlushLog(const logmessage &lg)
    {
        switch(_type)
        {
            case SCREEN_TYPE:
                FlushLogToScreen(lg);
                break;
            case FILE_TYPE:
                FlushLogToFile(lg);
                break;
        }
    }
    void LogMessage(std::string filename,int filenumber,int level,const char* format,...)  //介素可变参数
    {
        logmessage lg;

        lg._level = LevelToString(level);
        lg._id = getpid();
        lg._filename = filename;
        lg._filenumber =filenumber;
        lg._curr_time = GetCurTime();

        va_list ap;
        va_start(ap,format);    //初始化
        
        char log_info[1024];
        vsnprintf(log_info,sizeof(log_info),format,ap);

        va_end(ap);
        lg._message_info = log_info;

        //打印出来日志
        FlushLog(lg);
    }
    ~Log()
    {

    }
private:
    int _type;
    std::string _logfile;
};

// int main()
// {

//     return 0;
// }