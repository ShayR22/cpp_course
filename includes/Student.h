#ifndef __H_STUDENT__
#define __H_STUDENT__

#include "CourseInformation.h"
#include "Person.h"
#include "Course.h"

class Student : public Person
{
public:
	enum eDepartmenType { SOFTWARE, MEDICAL, ELECTRICITY };
private:
	eDepartmenType department;
	CourseInformation** courses;
	int numOfCourses;
	int maxOfCourses;

public:
	/******Constructors******/
	Student(const char* name, const Date& birthDate, const char* id, eDepartmenType department, int maxOfCourses = 20);
	Student(Student&& otherS);

	/******Gets/Sets******/
	eDepartmenType getDepartment() const { return department; }
	bool setDepartment(eDepartmenType newDepartmentType);
	const CourseInformation** getCourseInformation(int* numOfCourses) const; // also returning current num of grades
	void updateGrade(const Lecture& lecture, int newGrade) const; //searching in "grades" the Course (given by lecture),getting the Grade --- update the coures's grade
	bool addLecture(Lecture* newLecture);

	bool deleteFromCourse(Course& c); // finding the course the student is in, 
	//finding the lecture and deletes the student from lecture,then deletes the course from student's grades.

	/******print******/
	void printGrades() const;
	void printProfessores()const;
	virtual void print(ostream& os) const;

	const Student& operator+=(const Lecture& l);	//	use Student.addLecture


	/******Deconstructor******/
	~Student();

private:
	Student(const Student& otherS) = delete;
	Student& operator=(const Student& otherS) = delete;
	Student& operator=(Student&& otherS) = delete;
};

#endif