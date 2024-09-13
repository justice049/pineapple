#include<iostream>

class A
{
public:
	void PrintA()
	{
		std::cout << _a << std::endl;
	}
private:
	int _a;
};
int main()
{
	A* p = nullptr;
	p->PrintA();
	return 0;
}