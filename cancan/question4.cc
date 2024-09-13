#include<iostream>

//说说析构顺序捏

class Date
{
public:
	int _year;
	Date(int year)
	{
		_year = year;
	}
	~Date()
	{
		std::cout << "~Date" << _year << std::endl;
	}
};
static Date d5(5);
Date d6(6);
int main()
{
	Date d1(1);
	Date d2(2);
	Date d3(3);
	static Date d4(4);
	return 0;
}