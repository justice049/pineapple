#include<iostream>

class A
{
public:
	void PrintA()
	{
		std::cout << "快去炫鸡蛋仔" << std::endl;
	}
private:
	int _a;
};
int main()
{
	A* p = nullptr;
	(*p).PrintA();
	return 0;
}