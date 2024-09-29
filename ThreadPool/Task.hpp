#pragma once

#include <iostream>
#include <string>

class Task 
{
public:
    Task() : x(0), y(0) 
    {}
    Task(int a, int b) : x(a), y(b) 
    {}

    // 执行任务，计算结果
    void operator()() 
    {
        result_value = x + y; // 示例操作：计算 x 和 y 的和
    }

    // 返回结果
    int result() const 
    {
        return result_value;
    }

    // 调试输出
    std::string debug() const 
    {
        return "Task: x = " + std::to_string(x) + ", y = " + std::to_string(y);
    }

private:
    int x; // 第一个参数
    int y; // 第二个参数
    int result_value; // 计算结果
};
