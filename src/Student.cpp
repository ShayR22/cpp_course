#include <iostream>
#include "Student.h"
#include "Professor.h"

using namespace std;

Student::Student(const char* name, const Date& birthDate, const char* id,
	eDepartmenType department, int maxOfCourses) noexcept(false):
	Person(name, birthDate, id), department(department), maxOfCourses(maxOfCourses), numOfCourses(0)
{
	if (maxOfCourses <= 0)
		throw - 1;
}

Student::Student(const Student& other) noexcept : Person(other), 
	department(other.department), maxOfCourses(other.maxOfCourses), numOfCourses(other.numOfCourses),
	courses(other.courses)
{

}

Student& Student::operator=(const Student& other)
{
	Person::operator=(other);

	this->maxOfCourses = other.maxOfCourses;
	this->numOfCourses = other.numOfCourses;
	this->courses = other.courses;

	return *this;
}

Student& Student::operator=(Student&& other) noexcept
{
	Person::operator=(other);

	this->maxOfCourses = other.maxOfCourses;
	this->numOfCourses = other.numOfCourses;
	this->courses = move(other.courses);
	other.maxOfCourses = 0;
	other.numOfCourses = 0;
	return *this;
}

const char* Student::getDepartmentString() const
{
	if (department == eDepartmenType::SOFTWARE)
		return "Software";
	else if (department == eDepartmenType::MEDICAL)
		return "Medical";
	else
		return "Electricity";
}

Student::Student(Student&& otherS) noexcept : Person(otherS), department(otherS.department),
	maxOfCourses(otherS.maxOfCourses), numOfCourses(otherS.numOfCourses)
{
	courses = move(otherS.courses);
}

void Student::setDepartment(eDepartmenType newDepartmentType)
{
	department = newDepartmentType;
}

const GenericLinkedList<CourseInformation> Student::getCourseInformation(int* numOfCourses) const
{
	*numOfCourses = this->numOfCourses;
	return courses;
}

bool Student::isValidGrade(int grade) const
{
	return grade >= 1 && grade <= 100;
}

bool Student::updateGrade(const Lecture& lecture, int newGrade)
{
	if (!isValidGrade(newGrade))
		return false;

	CourseInformation temp(&lecture, newGrade);
	return courses.update(temp);
}

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
	CourseInformation temp(newLecture);
	courses.addTToEnd(temp);
	return true;
}

bool Student::deleteFromCourse(Course& c)
{
	map<int, Lecture*> lectures = c.getLectures();

	for (auto &e : lectures)
	{
		if (e.second->removeStudent(*this))
			return true;
	}
	return false;
}

bool Student::passedCourse(const Course* c)
{	
	for (int i = 0; i < numOfCourses; i++)
	{
		const Course& cur_c = courses[i]->getLecture()->getCourse();
		if (*c == cur_c)
			return true;
	}
	return false;
}

bool Student::qualify(const Course& c)
{
	const map<string, const Course*> conditionCourses = c.getConditionsCourses();
	for (auto &e : conditionCourses)
		if (!passedCourse(e.second))
			return false;

	return true;
}

void Student::printGrades(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "haven't finished any courses" << endl;
		return;
	}
	courses.printT(os);
}

void Student::printProfessores(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "doesn't have any courses, thus, no proffesors" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		const Professor& p = courses[i]->getLecture()->getLecturer();	
		p.print(os);
	}
}

void Student::printProfessoresNames(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "doesn't have any courses, thus, no proffesors" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		const Professor& p = courses[i]->getLecture()->getLecturer();
		os << p.getName() << " (id:" << p.getId() << ")";
		if (i < numOfCourses - 1)
			os << ", ";
		else
			os << endl;
	}
}

void Student::printAddition(ostream& os) const
{
	os << "Department: " << getDepartmentString() << endl;
	printGrades(os);
	printProfessoresNames(os);
}

void Student::print(ostream& os) const
{
	Person::print(os);
	Student::printAddition(os);
}

const Student& Student::operator+=(const Lecture& l)
{
	if (!addLecture(&l))
		cout << "failed to add lecture" << endl;
	return *this;
}

