#include "Professor.h"
#include <iostream>

using namespace std;

Professor::Professor(const string& name, const Date& birthDate, const string& id, double salary, int maxOfLectures) noexcept(false):
	Person(name, birthDate, id), salary(salary), maxOfLectures(maxOfLectures)
{
	if (maxOfLectures <= 0)
		throw "max lectures given must be a positive number";
	if (salary < 0)
		throw "Professor salary cant be a negative number";
}

Professor::Professor(const Professor& other) noexcept : Person(other)
{
	*this = other;
}

Professor::Professor(Professor&& other) noexcept : Person(other)
{
	*this = other;
}

const Professor& Professor::operator=(const Professor& other)
{
	Person::operator=(other);

	salary = other.salary;
	maxOfLectures = other.maxOfLectures;
	lectures = other.lectures;

	return *this;
}

const Professor& Professor::operator=(Professor&& other) noexcept
{
	Person::operator=(other);
	salary = other.salary;
	maxOfLectures = other.maxOfLectures;
	lectures = other.lectures;
	return *this;
}

Professor::~Professor()
{}

bool Professor::setSalary(double new_salary)
{
	if (salary < 0)
	{
		cout << "salary cant be a negative number" << endl;
		return false;
	}

	salary = new_salary;
	return true;
}

bool Professor::removeLecture(const Lecture* lectureToRemove)
{
	if (!lectures.erase(lectureToRemove->getId()))
	{
		cout << "Failed to remove lecture, lecture does not exists" << endl;
		return false;
	}
	return true;
}

bool Professor::addLectureTeaching(const Lecture* newLecture)
{
	if (!newLecture)
	{
		cout << "cant add null as new lecturer" << endl;
		return false;
	}

	if ((int)lectures.size() >= maxOfLectures)
	{
		cout << "lectueres are full and cant add more lecturers" << endl;
		return false;
	}

	lectures[newLecture->getId()] = newLecture;
	return true;
}

void Professor::printLectures(ostream& os) const
{
	if (lectures.size() == 0)
		os << "no lecutres" << endl;

	for (auto& e : lectures)
		os << *(e.second);
}

void Professor::printLecturesNames(ostream& os) const
{
	if (lectures.size() == 0)
	{
		os << "no lecutres" << endl;
		return;
	}

	os << "Lecturers ids to teach: ";
	unsigned int size = lectures.size();
	unsigned int index = 0;
	for (auto& e : lectures)
	{
		os << e.first;
		if (++index < size)
			os << ", ";
	}

	os << endl;
}

void Professor::printAddition(std::ostream& os) const
{
	os << "Salary: " << salary << endl;
	printLecturesNames(os);
}

void Professor::print(ostream& os) const
{
	Person::print(os);
	Professor::printAddition(os);
}

const Professor& Professor::operator+=(const Lecture& l)
{
	if (!addLectureTeaching(&l))
		cout << "Failed to add lecture" << endl;

	return *this;
}

const Professor& Professor::operator-=(const Lecture& l)
{
	if (!removeLecture(&l))
		cout << "Failed to add lecture" << endl;

	return *this;
}
