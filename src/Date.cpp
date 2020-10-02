#include <iostream>
#include "Date.h"

using namespace std;

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool Date::setYear(int newYear)
{
	if (newYear < 0)
		return false;

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

bool Date::setDay(int newDay)
{
	if (newDay < 0 || newDay > getNumOfDaysInYearMonth())
		return false;

	day = newDay;
	return true;
}

void Date::print() const
{
	cout << "year: " << year << ", month: " << month << ", day: " << day << endl;
}
