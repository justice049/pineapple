#include<iostream>

int Sum(int start,int end)
{
    int sum = 0;
    for(int i = start;i <= end;i++)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    int total = Sum(0,100);
    std::cout << "total: " << total << std::endl;

    return 0;
}