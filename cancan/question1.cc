#include<iostream>

class F1
{
public:
	void f2()
	{
		std::cout << "下一秒我在台北看烟火" << std::endl;
	}
};
int main()
{
	F1 f1;
	F1* pf1=&f1;
	pf1->f2();
 
	F1* pf2 = nullptr;
	pf2->f2();
 
	return 0;
}