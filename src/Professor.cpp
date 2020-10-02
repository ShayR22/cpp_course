#include "Professor.h"

Professor::Professor(const char* name, const Date& birthDate, const char* id, double salary, int maxOfLectures) :
	Person(name, birthDate, id)
{

}

bool Professor::setSalary(double new_salary)
{
	return false;
}

Lecture** Professor::getLectures(int* numOfLectures) const
{
	return nullptr;
}

bool Professor::removeLecture(Lecture* lectureToRemove)
{
	return false;
}

bool Professor::addLectureTeaching(Lecture* newLecture)
{
	return false;
}

bool Professor::setGrades(const Lecture& c)
{
	return false;
}
 // each student gives to professor the "GRADE" obj , the prof needs to update

void Professor::printLectures() const
{

}

void Professor::print(ostream& os) const
{

}

const Professor& Professor::operator+=(const Lecture& l)
{
	return *this;
} // use Professor.addLecture

const Professor& Professor::operator-=(const Lecture& l)
{
	return *this;
} // use Professor.removeLecture

Professor::~Professor()
{

}

