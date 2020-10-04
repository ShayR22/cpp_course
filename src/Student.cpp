#include "Student.h"

Student::Student(const char* name, const Date& birthDate, const char* id,
				 eDepartmenType department, int maxOfCourses) :
	Person(name, birthDate, id)
{

}

Student::Student(Student&& otherS) : Person(otherS)
{

}

bool Student::setDepartment(eDepartmenType newDepartmentType)
{
	return false;
}

const CourseInformation** Student::getCourseInformation(int* numOfCourses) const
{
	return nullptr;
} // also returning current num of grades

void Student::updateGrade(const Lecture& lecture, int newGrade) const
{

} //searching in "grades" the Course (given by lecture),getting the Grade --- update the coures's grade

bool Student::addLecture(Lecture* newLecture)
{
	return false;
}

// finding the course the student is in, 
// finding the lecture and deletes the student from lecture,then deletes the course from student's grades.
bool Student::deleteFromCourse(Course& c)
{
	return false;
}

void Student::printGrades() const
{

}

void Student::printProfessores()const
{

}

void Student::print(ostream& os) const
{

}

const Student& Student::operator+=(const Lecture& l)
{
	return *this;
} // use Student.addLecture

Student::~Student()
{

}

