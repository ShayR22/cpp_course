#ifndef __H_PROFESSOR__
#define __H_PROFESSOR__


#include "Person.h"
#include "Course.h"


class Professor : virtual public Person
{
private:
	/******Attributes******/
	double salary;
	Lecture** lectures;
	int maxOfLectures;
	int numOfLectures;

public:
	/******Constructors******/
	Professor(const char* name, const Date& birthDate, const char* id, double salary, int maxOfLectures = 5);//Constructor


	/******Gets/Sets******/
	bool setSalary(double new_salary);
	double getSalary() const { return salary; }
	Lecture** getLectures(int* numOfLectures)const;
	bool removeLecture(Lecture* lectureToRemove);
	bool addLectureTeaching(Lecture* newLecture);

	bool setGrades(const Lecture& c); // each student gives to professor the "GRADE" obj , the prof needs to update

	/******print******/
	void printLectures() const;
	virtual void print(ostream& os) const;

	const Professor& operator+=(const Lecture& l);	//	use Professor.addLecture
	const Professor& operator-=(const Lecture& l);	//	use Professor.removeLecture

	/******Deconstructor******/
	~Professor();

private:
	Professor(const Professor& otherP) = delete;
	Professor(Professor&& otherP) = delete;
	Professor& operator=(const Professor& otherP) = delete;
	Professor& operator=(Professor& otherP) = delete;
};
#endif