#ifndef __H_STUDENT__
#define __H_STUDENT__

#include "CourseInformation.h"
#include "Person.h"
#include "Course.h"
#include "GenericLinkedList.h"

class Student : virtual public Person
{
public:
	enum class eDepartmenType { SOFTWARE, MEDICAL, ELECTRICITY };
private:
	eDepartmenType department;
	GenericLinkedList<CourseInformation> courses;
	int numOfCourses;
	int maxOfCourses;
	bool passedCourse(const Course* c);
	bool isValidGrade(int grade) const;

protected:
	virtual void printAddition(std::ostream& os) const;

public:
	Student(const char* name, const Date& birthDate, const char* id,
			eDepartmenType department, int maxOfCourses = 20) noexcept(false);
	Student(const Student& other) noexcept;
	Student(Student&& otherS) noexcept;

	Student& operator=(const Student& other);
	Student& operator=(Student&& other) noexcept;

	eDepartmenType getDepartment() const { return department; }
	const char* getDepartmentString() const;

	void setDepartment(eDepartmenType newDepartmentType);
	const GenericLinkedList<CourseInformation> getCourseInformation(int* numOfCourses) const;
	bool updateGrade(const Lecture& lecture, int newGrade);
	bool addLecture(const Lecture* newLecture);

	bool deleteFromCourse(Course& c);
	bool qualify(const Course& c);

	void printGrades(std::ostream& os) const;
	void printProfessores(std::ostream& os) const;
	void printProfessoresNames(std::ostream& os) const;
	virtual void print(std::ostream& os) const;

	const Student& operator+=(const Lecture& l);
};

#endif /* __H_STUDENT__ */
