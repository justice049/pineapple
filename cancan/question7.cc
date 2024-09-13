#include<iostream>
int main()
{
    int array[] = { 1, 2, 3, 4, 5 };
    for(auto e : array)
        e *= 2;
    for(auto e : array)
        std::cout << e << " ";

    int array2[] = { 1, 2, 3, 4, 5 };
    for(auto& e : array)
        e *= 2;
    for(auto e : array)
        std::cout << e << " ";
}