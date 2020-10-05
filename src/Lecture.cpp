#include <ostream>
#include "Lecture.h"
#include "Student.h"

#define OPENING_HOUR 8
#define CLOSING_HOUR 23
#define LECTURE_MIN_DURATION 1
#define LECTURE_MAX_DURATION 6
#define LECTURE_MAX_NUM_STUDENTS 50
#define LECTURE_MAX_WAITING_LIST 30

using namespace std;

Lecture::Lecture(eWeekDay day, int startHour, int duration, eType type, Course& course,
	const ClassRoom& classRoom, const Professor& lecturer, const Lecture* practice,
	int maxStudentList, int maxWaitingList) noexcept(false) :
	course(&course), classRoom(&classRoom), lecturer(&lecturer), practice(practice),
	day(day), type(type), maxStudentList(maxStudentList), maxWaitingList(maxWaitingList),
	numOfStudentList(0), numOfWaitingList(0), studentList(nullptr), waitingList(nullptr)
{

	if(!this->setHour(startHour))
		throw "Invalid hour, hour must be between 8:00 and 22:00";
	if (!this->setDuration(duration))
		throw "Invalid duration, duration cant exceed 23:00";
	if (maxStudentList < 0)
		throw "Invalid max student size must be a positive number";
	if (maxWaitingList < 0)
		throw "Invalid max student size must be a positive number";

	this->studentList = new const Student* [this->maxStudentList];
	this->waitingList = new const Student* [this->maxWaitingList];

}

Lecture::Lecture(const Lecture& otherL) noexcept :
	studentList(nullptr), waitingList(nullptr)
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

void Lecture::setWeekDay(eWeekDay day) { this->day = day; }

int Lecture::getHour() const 
{ 
	return this->startHour; 
}

bool Lecture::setHour(int newHour)
{	
	if (newHour < OPENING_HOUR || newHour > CLOSING_HOUR - this->duration)
		return false;
	
	this->startHour = newHour;
	return true;
}

int Lecture::getDuration() const 
{ 
	return this->duration; 
}

bool Lecture::setDuration(int newDuration)
{	
	if (newDuration <= 0)
		this->duration = LECTURE_MIN_DURATION;

	if(this->startHour + newDuration > CLOSING_HOUR)
		return false;
	
	else
		this->duration = newDuration;

	return true;
}

int Lecture::getMaxStudentsList() const
{
	return this->maxStudentList;
}

bool Lecture::setMaxStudentsList(int newMaxStudentsList)
{	
	if (newMaxStudentsList < 0)
		return false;
	if (newMaxStudentsList > LECTURE_MAX_NUM_STUDENTS)
		this->maxStudentList = LECTURE_MAX_NUM_STUDENTS;
	else
		this->maxStudentList = newMaxStudentsList;

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

const Student*const* Lecture::getStudentList(int* numOfStudentList) const
{
	*numOfStudentList = this->numOfStudentList;
	return this->studentList;
}

const Student*const* Lecture::getWaitingList(int* numOfWaitingList) const
{
	*numOfWaitingList = this->numOfWaitingList;
	return this->waitingList;
}

bool Lecture::addStudent(const Student& newStudent)
{	
	if (this->numOfStudentList == LECTURE_MAX_NUM_STUDENTS)
		return false;

	this->studentList[this->numOfStudentList] = &newStudent;
	this->numOfStudentList++;
	return true;
}

bool Lecture::removeStudent(Student& studentToRemove)
{
	for (int i = 0; i < this->numOfStudentList; i++)
	{
		if (*(this->studentList[i]) == studentToRemove.getId())
			removeStudentByIndex(i, this->studentList, this->numOfStudentList);
		return true;
	}
	return false;
}


bool Lecture::addToWaitingList(const Student& newStudent)
{	
	if (this->numOfWaitingList == LECTURE_MAX_WAITING_LIST)
		return false;

	this->waitingList[this->numOfWaitingList] = &newStudent;
	this->numOfWaitingList++;
	return true;
}

bool Lecture::removeFromWaitingList(const Student& studentToRemove)
{
	for (int i = 0; i < this->numOfWaitingList; i++)
	{
		if (*(this->waitingList[i]) == studentToRemove.getId())
			removeStudentByIndex(i, this->waitingList, this->numOfWaitingList);
		return true;
	}
	return false;
}

void Lecture::removeStudentByIndex(int index, const Student** ptrArray, int arraySize)
{
	if (index > arraySize - 1)
		return;

	int numEleToMove = arraySize - index - 1;

	delete ptrArray[index];
	/* copy and override the array in order to keep it ordered */
	if (numEleToMove != 0)
		memmove((void*)&(ptrArray[index]), (void*)&(ptrArray[index + 1]), sizeof(Student*) * numEleToMove);

	ptrArray[arraySize--] = nullptr;
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
	course = otherL.course;
	classRoom = otherL.classRoom;
	lecturer = otherL.lecturer;
	practice = otherL.practice;
			
	day = otherL.day;
	type = otherL.type;
	startHour = otherL.startHour;
	duration = otherL.duration;

	delete studentList;
	delete waitingList;

	numOfStudentList = otherL.numOfStudentList;
	numOfWaitingList = otherL.numOfWaitingList;
	maxStudentList = otherL.maxStudentList;
	maxWaitingList = otherL.maxWaitingList;

	this->studentList = new const Student * [this->maxStudentList];
	this->waitingList = new const Student * [this->maxWaitingList];
	memcpy((void*)studentList, (void*)otherL.studentList, sizeof(Student*) * numOfStudentList);
	memcpy((void*)waitingList, (void*)otherL.waitingList, sizeof(Student*) * numOfWaitingList);

	return *this;
}

Lecture& Lecture::operator=(Lecture&& otherL) noexcept
{
	course = otherL.course;
	classRoom = otherL.classRoom;
	lecturer = otherL.lecturer;
	practice = otherL.practice;

	day = otherL.day;
	type = otherL.type;
	startHour = otherL.startHour;
	duration = otherL.duration;

	numOfStudentList = otherL.numOfStudentList;
	numOfWaitingList = otherL.numOfWaitingList;
	maxStudentList = otherL.maxStudentList;
	maxWaitingList = otherL.maxWaitingList;
	
	studentList = otherL.studentList;
	waitingList = otherL.waitingList;

	otherL.studentList = nullptr;
	otherL.waitingList = nullptr;

	otherL.numOfStudentList = 0;
	otherL.numOfWaitingList = 0;
	otherL.maxStudentList = 0;
	otherL.maxWaitingList = 0;

	return *this;
}


ostream& operator<<(ostream& os, const Lecture& l)
{
	os << "Course: " << l.course << ", Lecture Day: " << l.day << ", Starting Hour: " << l.startHour << 
		", Duration: " << l.duration << ", Type: " << l.type << ", Practice: " << l.practice << endl;

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

Lecture::~Lecture()
{
	delete studentList;
	delete waitingList;
}

int Lecture::automaticID = 0;