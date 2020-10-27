#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}
Date::Date(const Date& other) { *this = other; }

bool Date::setYear(int newYear)
{
	if (newYear < 0)
		return false;

	year = newYear;
	return true;
}

bool Date::setMonth(int newMonth)
{
	if (newMonth < 0 || newMonth > 12)
		return false;

	month = newMonth;
	return true;
}

int Date::getNumOfDaysInYearMonth()
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (month != 2)
		return 30;

	//leap year condition for febuary
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return 29;
	else
		return 28;
}

inline bool Date::setDay(int newDay)
{
	if (newDay < 0 || newDay > getNumOfDaysInYearMonth())
		return false;

	day = newDay;
	return true;
}

Date& Date::operator=(const Date& other)
{
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	return *this;
}

ostream& operator<< (ostream& os, const Date& d)
{
	os << "year: " << d.year << ", month: " << d.month << ", day: " << d.day << endl;
	return os;
}
