#ifndef __H_STUDENT__
#define __H_STUDENT__

#include "CourseInformation.h"
#include "Person.h"
#include "Course.h"

class Student : virtual public Person
{
public:
	enum class eDepartmenType { SOFTWARE, MEDICAL, ELECTRICITY };
private:
	eDepartmenType department;
	CourseInformation** courses;
	int numOfCourses;
	int maxOfCourses;
	void destroyCourses();

public:
	Student(const char* name, const Date& birthDate, const char* id,
			eDepartmenType department, int maxOfCourses = 20) noexcept(false);
	Student(const Student& other) noexcept;
	Student(Student&& otherS) noexcept;

	Student& operator=(const Student& other);
	Student& operator=(Student&& other) noexcept;

	~Student();

	eDepartmenType getDepartment() const { return department; }
	void setDepartment(eDepartmenType newDepartmentType);
	const CourseInformation * const * getCourseInformation(int* numOfCourses) const;
	bool updateGrade(const Lecture& lecture, int newGrade) const; 
	bool addLecture(const Lecture* newLecture);

	bool deleteFromCourse(Course& c);

	void printGrades(std::ostream& os) const;
	void printProfessores(std::ostream& os)const;
	virtual void print(std::ostream& os) const;

	const Student& operator+=(const Lecture& l);
};

#endif /* __H_STUDENT__ */
