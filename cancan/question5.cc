#include<iostream>
#include<assert.h>
using namespace std;
 
class Date
{
public:
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& tmp)
	{
		_year = tmp._year;
		_month = tmp._month;
		_day = tmp._day;
	}
	//获取某年某月天数
	int GetMonthDay(int year,int month)
	{
		assert(month > 0 && month < 13);
		static int days[13] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[month];
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			day += 1;
		}
		return day;
	}
	Date& operator++()
	{
		_day += 1;
		return *this;
	}
	Date operator++(int)
	{
		Date tmp = (*this);
		_day += 1;
		return tmp;
	}
	Date& operator--()
	{
		_day -= 1;
		return *this;
	}
	Date operator--(int)
	{
		Date tmp = (*this);
		_day -= 1;
		return tmp;
	}
    Date& operator+=(int day);
	Date operator+(int day);
private:
	int _year;
	int _month;
	int _day;
};

//第一种捏
Date& Date::operator+=(int day)
{
	_day += day;
	while (_day>GetMonthDay(_year,_month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}
 
//可以拷贝构造
Date Date::operator+(int day)
{
	Date tmp = Date(*this);
	tmp += day;
	return tmp;
}

//第二种捏
Date Date::operator+(int day)
{
	Date tmp = Date(*this);
	tmp._day += day;
	while (tmp._day > GetMonthDay(tmp._year, tmp._month))
	{
		tmp._day -= GetMonthDay(tmp._year, tmp._month);
		tmp._month++;
		if (tmp._month > 12)
		{
			tmp._year++;
			tmp._month = 1;
		}
	}
	return tmp;
}
 
Date& Date::operator+=(int day)
{
	*this = *this + day;
	return *this;
}