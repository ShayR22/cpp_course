#include <iostream>
#include "Student.h"
#include "Professor.h"

using namespace std;

Student::Student(const char* name, const Date& birthDate, const char* id,
	eDepartmenType department, int maxOfCourses) noexcept(false):
	Person(name, birthDate, id), department(department), maxOfCourses(maxOfCourses), numOfCourses(0),
	courses(nullptr)
{
	if (maxOfCourses <= 0)
		throw - 1;
	courses = new CourseInformation*[maxOfCourses];
}

Student::Student(Student&& otherS) noexcept : Person(otherS), department(otherS.department),
	maxOfCourses(otherS.maxOfCourses), numOfCourses(otherS.numOfCourses)
{
	courses = otherS.courses;
	otherS.courses = nullptr;
}

void Student::setDepartment(eDepartmenType newDepartmentType)
{
	department = newDepartmentType;
}

const CourseInformation * const * Student::getCourseInformation(int* numOfCourses) const
{
	*numOfCourses = this->numOfCourses;
	return courses;
}

void Student::updateGrade(const Lecture& lecture, int newGrade) const
{
	for (int i = 0; i < numOfCourses; i++)
	{
		if (lecture.getId() == courses[i]->getLecture()->getId())
		{
			courses[i]->setGrade(newGrade);
		}

	}
} //searching in "grades" the Course (given by lecture),getting the Grade --- update the coures's grade

bool Student::addLecture(const Lecture* newLecture)
{
	if (!newLecture)
	{
		cout << "Lecturer cant be null" << endl;
		return false;
	}
	if (numOfCourses >= maxOfCourses)
	{
		cout << "Courses are full, cant take any more courses" << endl;
		return false;
	}

	courses[numOfCourses++] = new CourseInformation(newLecture);
	return true;
}

// finding the course the student is in, 
// finding the lecture and deletes the student from lecture,then deletes the course from student's grades.
bool Student::deleteFromCourse(Course& c)
{
	int numLectures;
	Lecture** lectures_ptrs = c.getLectures(&numLectures);

	for (int i = 0; i < numLectures; i++)
	{
		Lecture* cur_lec = lectures_ptrs[i];
		if (cur_lec->removeStudent(*this))
			return true;
	}
	return false;
}

void Student::printGrades() const
{
	if (numOfCourses == 0)
	{
		Person::print(cout);
		cout << "haven't finished any courses" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		courses[i]->print();
	}
}

void Student::printProfessores()const
{
	if (numOfCourses == 0)
	{
		Person::print(cout);
		cout << "doesn't have any courses, thus, no proffesors" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		const Professor& p = courses[i]->getLecture()->getLecturer();
		p.print(cout);
	}
}

void Student::print(ostream& os) const
{
	Person::print(cout);
	printGrades();
	printProfessores();
}

const Student& Student::operator+=(const Lecture& l)
{
	if (!addLecture(&l))
		cout << "failed to add lecture" << endl;
	return *this;
}

Student::~Student()
{
	for (int i = 0; i < numOfCourses; i++)
		delete courses[i];
	delete courses;
}

