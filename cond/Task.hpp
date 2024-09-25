#pragma once

//加法
class Task
{
public:
    Task()
    {

    }
    ~Task()
    {

    }
    int Excute()
    {
        return _x+_y;
    }
private:
    int _x;
    int _y;
};

