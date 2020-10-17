#include "Professor.h"
#include <iostream>

using namespace std;

Professor::Professor(const char* name, const Date& birthDate, const char* id, double salary, int maxOfLectures) noexcept(false):
	Person(name, birthDate, id), salary(salary), maxOfLectures(maxOfLectures), numOfLectures(0), lectures(nullptr)
{
	if (maxOfLectures <= 0)
		throw "max lectures given must be a positive number";
	if (salary < 0)
		throw "Professor salary cant be a negative number";

	lectures = new const Lecture*[maxOfLectures];
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
	numOfLectures = other.numOfLectures;

	delete lectures;
	lectures = new const Lecture * [maxOfLectures];

	for (int i = 0; i < maxOfLectures; i++)
	{
		if (i < numOfLectures)
			lectures[i] = other.lectures[i];
		else
			lectures[i] = nullptr;
	}
	return *this;
}

const Professor& Professor::operator=(Professor& other) noexcept
{
	Person::operator=(other);
	salary = other.salary;

	maxOfLectures = other.maxOfLectures;
	numOfLectures = other.numOfLectures;
	lectures = other.lectures;
	other.lectures = nullptr;
	return *this;
}

Professor::~Professor()
{
	delete lectures;
}

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

const Lecture* const* Professor::getLectures(int* numOfLectures) const
{
	*numOfLectures = this->numOfLectures;
	return lectures;
}

void Professor::removeLectureByIndex(int index)
{
	/* invalid element index */
	if (index > numOfLectures - 1)
		return;

	int numEleToMove = numOfLectures - index - 1;

	delete lectures[index];
	/* copy and override the array in order to keep it ordered */
	if (numEleToMove != 0)
		memmove(&lectures[index], &lectures[index + 1], sizeof(Lecture*) * numEleToMove);

	lectures[--numOfLectures] = nullptr;
}

int Professor::getLectureIndex(const Lecture& find)
{
	for (int i = 0; i < numOfLectures; i++)
		if (lectures[i]->getId() == find.getId())
			return i;
	return -1;
}

bool Professor::removeLecture(const Lecture* lectureToRemove)
{
	int idx = getLectureIndex(*lectureToRemove);
	if (idx < 0)
		return false;

	removeLectureByIndex(idx);
	return true;
}

bool Professor::addLectureTeaching(const Lecture* newLecture)
{
	if (!newLecture)
	{
		cout << "cant add null as new lecturer" << endl;
		return false;
	}
	if (numOfLectures >= maxOfLectures)
	{
		cout << "lectueres are full and cant add more lecturers" << endl;
		return false;
	}

	lectures[numOfLectures++] = newLecture;
	return true;
}

void Professor::printLectures(ostream& os) const
{
	if (numOfLectures == 0)
		os << "no lecutres" << endl;

	for (int i = 0; i < numOfLectures; i++)
		os << *lectures[i];
}

void Professor::printLecturesNames(ostream& os) const
{
	if (numOfLectures == 0)
	{
		os << "no lecutres" << endl;
		return;
	}

	os << "Lecturers ids to teach: ";
	for (int i = 0; i < numOfLectures; i++)
	{
		os << lectures[i]->getId();
		if (i < numOfLectures - 1)
			os << ", ";
		else
			os << endl;
	}
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
