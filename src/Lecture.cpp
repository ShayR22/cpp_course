#include <ostream>
#include "Lecture.h"

using namespace std;

Lecture::Lecture(eWeekDay day, int startHour, int duration, eType type, Course& course,
				 const ClassRoom& classRoom, const Professor& lecturer, Lecture* practice,
				 int maxStudentList, int maxWaitingList ) :
	course(course), classRoom(&classRoom), lecturer(&lecturer), practice(practice)
{

}

Lecture::Lecture(const Lecture& other) :
course(other.course), classRoom(other.classRoom), lecturer(other.lecturer), practice(other.practice)

{

}


bool Lecture::operator==(const Lecture& l) const
{
	return true;
}

Lecture& Lecture::operator=(const Lecture& otherL)
{
	return *this;
}

Lecture& Lecture::operator=(Lecture&& otherL)
{
	return *this;
}

bool Lecture::setWeekDay(eWeekDay day)
{
	return false;
}

bool Lecture::setHour(int newHour)
{
	return false;
}

bool Lecture::setDuration(int newDuration)
{
	return false;
}

bool Lecture::setMaxStudentsList(int newMaxStudentsList)
{
	return false;
}
 //Check that: "ClassRoom->maxSeats >= newMaxStudentList" 
bool Lecture::setLectureType(const eType newType)
{
	return false;
}

bool Lecture::setClassRoom(const ClassRoom* newClassRoom)
{
	return false;
}

bool Lecture::setLecturer(const Professor& newLectureProfessor)
{
	return false;
}

const Student** Lecture::getStudentList(int* numOfStudentList) const
{
	return nullptr;
}// returning also the "current number of students"


bool Lecture::addStudent(const Student& newStudent)
{
	return false;
}

bool Lecture::removeStudent(Student& studentToRemove)
{
	return false;
}

bool Lecture::addToWaitingList(const Student& newStudent)
{
	return false;
}

bool Lecture::removeFromWaitingList(const Student& studentToRemove)
{
	return false;
}

bool Lecture::setPracticeLecture(const Lecture& newPracticeLecture)
{
	return false;
}

ostream& operator<<(ostream& os, const Lecture& l)
{
	return os;
}

Lecture::~Lecture()
{

}

int Lecture::automaticID = 0;