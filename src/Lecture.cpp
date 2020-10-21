#define _CRT_SECURE_NO_WARNINGS

#include <ostream>
#include "Lecture.h"
#include "Student.h"
#include "Classroom.h"
#include <string>

#define OPENING_HOUR 8
#define CLOSING_HOUR 23
#define LECTURE_MIN_DURATION 1
#define LECTURE_MAX_DURATION 6

using namespace std;

Lecture::Lecture(eWeekDay day, int startHour, int duration, eType type, const Course& course,
	const ClassRoom& classRoom, const Professor& lecturer, const Lecture* practice,
	int maxStudentMap, int maxWaitingMap) noexcept(false) :
	course(&course), classRoom(&classRoom), lecturer(&lecturer), practice(practice),
	day(day), type(type), maxStudentMap(maxStudentMap), maxWaitingMap(maxWaitingMap)
{
	if(!this->setHour(startHour))
		throw "Invalid hour, hour must be between 8:00 and 22:00";
	if (!this->setDuration(duration))
		throw "Invalid duration, duration cant exceed 23:00";
	if (maxStudentMap < 0)
		throw "Invalid max student size must be a positive number";
	if (maxWaitingMap < 0)
		throw "Invalid max student size must be a positive number";

	this->id = this->automaticID++;
}

Lecture::Lecture(const Lecture& otherL) noexcept
{
	*this = otherL;
}

Lecture::Lecture(Lecture&& otherL) noexcept
{
	*this = otherL;
}

Lecture::eWeekDay Lecture::getWeekDay() const
{ 
	return this->day; 
}

void Lecture::setWeekDay(eWeekDay day)
{ 
	this->day = day;
}

int Lecture::getHour() const 
{ 
	return this->startHour; 
}

bool Lecture::setHour(int newHour)
{	
	if (newHour < OPENING_HOUR)
	{
		cout << "New hour given is not valid, hours must be above " << OPENING_HOUR << endl;
		return false;
	}
	if (newHour > CLOSING_HOUR - this->duration)
	{
		cout << "New hour given is not valid, hour + duration given must be below " << CLOSING_HOUR << endl;
		return false;
	}
	
	this->startHour = newHour;
	return true;
}

int Lecture::getDuration() const 
{ 
	return this->duration; 
}

bool Lecture::setDuration(int newDuration)
{	
	if (newDuration < LECTURE_MIN_DURATION)
	{
		cout << "Lecture duration cant be below " << LECTURE_MIN_DURATION << endl;
		return false;
	}
	if (newDuration > LECTURE_MAX_DURATION)
	{
		cout << "Lecture duration cant be above " << LECTURE_MAX_DURATION << endl;
		return false;
	}
	if (this->startHour + newDuration > CLOSING_HOUR)
	{
		cout << "Lecture duration cant exceed " << CLOSING_HOUR << endl;
		return false;
	}
	
	this->duration = newDuration;

	return true;
}

int Lecture::getMaxStudentsMap() const
{
	return this->maxStudentMap;
}

bool Lecture::setMaxStudentsMap(int newMaxStudentsMap)
{	
	if (newMaxStudentsMap < this->studentMap.size())
	{
		cout << "Max student Map number cant be below the num of students that currently in the Map" << endl;
		return false;
	}

	this->maxStudentMap = newMaxStudentsMap;
	return true;
}

int Lecture::getMaxWaitingsMap() const
{
	return this->maxWaitingMap;
}

bool Lecture::setMaxWaitingMap(int newMaxWaitingMap)
{
	if (newMaxWaitingMap < this->waitingMap.size())
	{
		cout << "Max waiting Map number cant be below the num of students waiting that currently in the Map" << endl;
		return false;
	}

	this->maxWaitingMap = newMaxWaitingMap;
	return true;
}

Lecture::eType Lecture::getLectureType() const 
{ 
	return this->type; 
}

void Lecture::setLectureType(const eType newType)
{	
	this->type = newType;
}

const ClassRoom& Lecture::getClassRoom() const
{ 
	return *(this->classRoom); 
}

void Lecture::setClassRoom(const ClassRoom* newClassRoom)
{
	this->classRoom = newClassRoom;
}

const Professor& Lecture::getLecturer() const
{
	return *(this->lecturer);
}

void Lecture::setLecturer(const Professor& newLectureProfessor)
{	
	this->lecturer = &newLectureProfessor;
}

const map<string, const Student*> Lecture::getStudentMap() const
{
	return this->studentMap;
}

const map<string, const Student*> Lecture::getWaitingMap() const
{
	return this->waitingMap;
}

bool Lecture::addStudent(const Student& newStudent)
{	
	if (studentMap.find(newStudent.getId()) != studentMap.end())
	{
		cout << "Student already register in lecture" << endl;
		return false;
	}

	if (this->studentMap.size() == this->maxStudentMap)
	{
		cout << "Failed to add student, student Map is full" << endl;
		return false;
	}

	this->studentMap.insert({ newStudent.getId(), &newStudent });
	return true;
}

bool Lecture::removeStudent(Student& studentToRemove)
{	
	if (!studentMap.erase(studentToRemove.getId()))
	{
		cout << "Failed to remove student from student Map, student does not exists" << endl;
		return false;
	}
	return true;
}

bool Lecture::addToWaitingMap(const Student& newStudent)
{	
	if (this->waitingMap.size() == this->maxWaitingMap)
	{
		cout << "Failed to add student, student waiting Map is full" << endl;
		return false;
	}

	this->waitingMap.insert({ newStudent.getId(), &newStudent });
	return true;
}

bool Lecture::removeFromWaitingMap(const Student& studentToRemove)
{
	if (!waitingMap.erase(studentToRemove.getId()))
	{
		cout << "Failed to remove student from student waiting Map, student does not exists" << endl;
		return false;
	}
	return true;
}


const Lecture& Lecture::getPracticeLecture() const
{
	return *practice;
}

void Lecture::setPracticeLecture(const Lecture& newPracticeLecture)
{
	this->practice = &newPracticeLecture;
}

const Course& Lecture::getCourse() const
{
	return *course;
}

bool Lecture::operator==(int id) const
{
	return this->id == id; 
}

bool Lecture::operator==(const Lecture& l) const
{
	return this->id == l.id;
}

Lecture& Lecture::operator=(const Lecture& otherL) noexcept
{	
	this->id = otherL.id;
	this->course = otherL.course;
	this->classRoom = otherL.classRoom;
	this->lecturer = otherL.lecturer;
	this->practice = otherL.practice;
			
	this->day = otherL.day;
	this->type = otherL.type;
	this->startHour = otherL.startHour;
	this->duration = otherL.duration;

	this->maxStudentMap = otherL.maxStudentMap;
	this->maxWaitingMap = otherL.maxWaitingMap;

	this->studentMap = otherL.studentMap;
	this->waitingMap = otherL.waitingMap;

	return *this;
}

Lecture& Lecture::operator=(Lecture&& otherL) noexcept
{
	this->id = otherL.id;
	this->course = otherL.course;
	this->classRoom = otherL.classRoom;
	this->lecturer = otherL.lecturer;
	this->practice = otherL.practice;

	this->day = otherL.day;
	this->type = otherL.type;
	this->startHour = otherL.startHour;
	this->duration = otherL.duration;

	this->maxStudentMap = otherL.maxStudentMap;
	this->maxWaitingMap = otherL.maxWaitingMap;
	
	this->studentMap = move(otherL.studentMap);
	this->waitingMap = move(otherL.waitingMap);

	otherL.maxStudentMap = 0;
	otherL.maxWaitingMap = 0;

	return *this;
}

ostream& operator<<(ostream& os, const Lecture& l)
{
	char practiceID[16] = { 0 };
	if (l.practice != nullptr)
		sprintf(practiceID, "%d", l.practice->getId());

	os << "ID: " << l.getId() << ", Course: " << l.course->getCourseName() << ", Lecture Day: " << l.day << 
		", Starting Hour: " << l.startHour << ", Duration: " << l.duration << 
		", Type: " << l.type << ", Practice id: " << practiceID << endl;

	return os;
}

ostream& operator<<(ostream & os, Lecture::eWeekDay day)
{
	switch (day)
	{
		case Lecture::eWeekDay::SUNDAY:
			os << "Sunday";
			break;
		case Lecture::eWeekDay::MONDAY:
			os << "Monday";
			break;
		case Lecture::eWeekDay::TUESDAY:
			os << "Tuesday";
			break;
		case Lecture::eWeekDay::WEDNESDAY:
			os << "Wednesday";
			break;
		case Lecture::eWeekDay::THURSDAY:
			os << "Thursday";
			break;
		case Lecture::eWeekDay::FRIDAY:
			os << "Friday";
			break;
	}
	return os;
}

ostream& operator<<(ostream& os, Lecture::eType type)
{
	switch (type)
	{
	case Lecture::eType::PRACTICE:
		os << "Practice";
		break;
	case Lecture::eType::LECTURE:
		os << "Lecture";
		break;
	}
	return os;
}	

Lecture::~Lecture(){}

int Lecture::automaticID = 0;