#ifndef __H_DATE__
#define __H_DATE__

class Date
{
private:
	int year;
	int month;
	int day;
	inline int getNumOfDaysInYearMonth();
public:
	Date(int year, int month, int day);
	Date(const Date& other);
	
	int getYear() const { return year; }
	bool setYear(int newYear);
	int getMonth() const { return month; }
	bool setMonth(int newMonth);
	int getDay() const { return day; }
	bool setDay(int newDay);

	friend std::ostream& operator<<(std::ostream& os, const Date& d);

	Date& operator=(const Date& other);
};

#endif
