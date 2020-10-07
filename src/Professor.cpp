#include "Professor.h"
#include <iostream>

using namespace std;

Professor::Professor(const char* name, const Date& birthDate, const char* id, double salary, int maxOfLectures) noexcept(false):
	Person(name, birthDate, id), salary(salary), maxOfLectures(maxOfLectures), numOfLectures(0), lectures(nullptr)
{
	if (maxOfLectures <= 0)
		throw - 1;
	lectures = new const Lecture*[maxOfLectures];
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

/* TODO maybe change this function to include cosnt protection */
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
		memmove((void *)lectures[index], (void *)lectures[index + 1], sizeof(Lecture*) * numEleToMove);

	lectures[numOfLectures--] = nullptr;
}

bool Professor::removeLecture(const Lecture* lectureToRemove)
{
	for (int i = 0; i < numOfLectures; i++)
	{
		if (lectures[i]->getId() == lectureToRemove->getId())
		{
			removeLectureByIndex(i);
			return true;
		}
	}
	return false;
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

bool Professor::setGrades(const Lecture& c)
{
	return false;
}
 // each student gives to professor the "GRADE" obj , the prof needs to update

void Professor::printLectures() const
{
	if (numOfLectures == 0)
		cout << "no lecutres" << endl;

	for (int i = 0; i < numOfLectures; i++)
		cout << *lectures[i];

}

void Professor::print(ostream& os) const
{
	Person::print(os);
	printLectures();
}

const Professor& Professor::operator+=(const Lecture& l)
{
	if (!addLectureTeaching(&l))
		cout << "Failed to add lecture" << endl;

	return *this;
} // use Professor.addLecture

const Professor& Professor::operator-=(const Lecture& l)
{
	if (!removeLecture(&l))
		cout << "Failed to add lecture" << endl;

	return *this;
} // use Professor.removeLecture

Professor::~Professor()
{
	for (int i = 0; i < numOfLectures; i++)
		delete lectures[i];
	delete lectures;
}

