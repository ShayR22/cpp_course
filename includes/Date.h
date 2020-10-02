#ifndef __H_DATE__
#define __H_DATE__

class Date
{
private:
	int year;
	int month;
	int day;
	int getNumOfDaysInYearMonth();
public:
	/******Constructors******/
	Date(int year, int month, int day);
	
	/******Gets/Sets******/
	int getYear() const { return year; }
	bool setYear(int newYear);
	int getMonth() const { return month; }
	bool setMonth(int newMonth);
	int getDay() const { return day; }
	bool setDay(int newDay);

	/******print******/
	void print() const;

};

#endif
