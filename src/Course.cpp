#define _CRT_SECURE_NO_WARNINGS

#include <ostream>
#include <string>
#include <cmath>
#include "Course.h"
#include "Student.h"

#define EPSSILON 0.0000001

using namespace std;

Course::Course(const char* name, const Professor* coordinator, float points,
	int maxLectures, int maxConditionCourses) : 
	coordinator(coordinator), maxLectures(maxLectures), maxConditionCourses(maxConditionCourses),
	numOfLectures(0), numOfConditionCourses(0)
{
	if (!setCourseName(name))
		throw "ERROR: In class Course: name is nullptr";
	
	if(!setPoints(points))
		throw "ERROR: In class Course: points can't be negative or not divisible by 0.5";

	this->lectures = new Lecture * [maxLectures];
	this->conditionCourses = new const Course * [maxConditionCourses];
}

Course::Course(const Course& other) noexcept
{
	*this = other;
}

Course::Course(Course&& other) noexcept
{
	*this = other;
}

Course& Course::operator=(const Course& other)
{
	setCourseName(other.name);
	coordinator = other.coordinator;
	points = other.points;

	destroyLectures();
	maxLectures = other.maxLectures;
	numOfLectures = other.numOfLectures;
	lectures = new Lecture * [maxLectures];
	for (int i = 0; i < maxLectures; i++)
	{
		if (i < numOfLectures)
			lectures[i] = new Lecture(*other.lectures[i]);
		else
			lectures[i] = nullptr;
	}

	delete conditionCourses;
	maxConditionCourses = other.maxConditionCourses;
	numOfConditionCourses = other.numOfConditionCourses;
	conditionCourses = new const Course * [maxConditionCourses];
	for (int i = 0; i < maxConditionCourses; i++)
	{
		if (i < numOfConditionCourses)
			conditionCourses[i] = other.conditionCourses[i];
		else
			conditionCourses[i] = nullptr;
	}

	return *this;
}

Course& Course::operator=(Course&& other) noexcept
{
	name = other.name;
	other.name = nullptr;
	coordinator = other.coordinator;
	other.coordinator = nullptr;
	points = other.points;

	maxLectures = other.maxLectures;
	other.maxLectures = 0;
	numOfLectures = other.numOfLectures;
	other.numOfLectures = 0;
	lectures = other.lectures;
	other.lectures = nullptr;
	
	maxConditionCourses = other.maxConditionCourses;
	other.maxConditionCourses = 0;
	numOfConditionCourses = other.numOfConditionCourses;
	other.numOfConditionCourses = 0;
	conditionCourses = other.conditionCourses;
	other.conditionCourses = nullptr;

	return *this;
}

bool Course::operator==(const Course& other) const
{
	return strcmp(name, other.name) == 0;
}

bool Course::operator==(const char* name) const
{
	return strcmp(this->name, name) == 0;
}

void Course::destroyLectures()
{
	for (int i = 0; i < numOfLectures; i++)
		delete lectures[i];
	delete lectures;
}

bool Course::setCourseName(const char* newCourseName)
{
	if (name == nullptr)
		return false;

	if (name == this->name)
		return true;

	delete this->name;
	int length = strlen(name);
	this->name = new char[length];
	strcpy(this->name, name);
	return true;
}

bool Course::setCoordinator(const Professor* p)
{
	if (p == nullptr)
		return false;

	coordinator = p;
	return true;
}

inline bool Course::isNearlyEqual(double x, double y)
{
	const double epsilon = 1e-6;
	return abs(x - y) <= epsilon * abs(x);
}

bool Course::setPoints(float p)
{
	float remainder = p - (long)p;

	/* points can't be negative or not divisible by 0.5*/
	if (p < 0 || !isNearlyEqual(remainder, 0.5))
		return false;

	points = p;
	return true;
}

Lecture** Course::getLectures(int* numOfLectures) const
{
	*numOfLectures = this->numOfLectures;
	return lectures;
}

int Course::getLectureIndex(int id) const
{
	for (int i = 0; i < numOfLectures; i++)
		if (*lectures[i] == id)
			return i;
	return -1;
}

int Course::getLectureIndex(const Lecture& l) const
{
	return getLectureIndex(l.getId());
}

bool Course::removeLecture(const Lecture& lectureToRemove)
{
	int index = getLectureIndex(lectureToRemove);
	if (index < 0)
		return false;

	delete lectures[index];
	int numEleToMove = numOfLectures - index - 1;
	if (numEleToMove != 0)
		memmove(&lectures[index], &lectures[index + 1], sizeof(Lecture*) * numEleToMove);
	lectures[numOfLectures--] = nullptr;
	return true;
}

bool Course::removeLecture(int id)
{
	int index = getLectureIndex(id);
	if (index < 0)
		return false;

	delete lectures[index];
	int numEleToMove = numOfLectures - index - 1;
	if (numEleToMove > 0)
		memmove(&lectures[index], &lectures[index + 1], sizeof(Lecture*) * numEleToMove);
	lectures[--numOfLectures] = nullptr;

	return true;
}

bool Course::addLecture(const Lecture& lectureToAdd)
{
	if (numOfLectures >= maxLectures)
		return false;

	if (getLectureIndex(lectureToAdd) >= 0)
		return false;

	lectures[numOfLectures++] = new Lecture(lectureToAdd);
	return true;
}

const Course** Course::getConditionsCourses(int* numOfConditionCourses) const
{
	*numOfConditionCourses = this->numOfConditionCourses;
	return conditionCourses;
}

int Course::getConditionCourseIndex(const char* name) const
{
	for (int i = 0; i < numOfConditionCourses; i++)
		if (*conditionCourses[i] == name)
			return i;
	return -1;
}

int Course::getConditionCourseIndex(const Course& c) const
{
	return getConditionCourseIndex(c.name);
}

bool Course::removeConditionCourse(const Course& c)
{
	int index = getConditionCourseIndex(c);
	if (index < 0)
		return false;

	int numEleToMove = numOfConditionCourses - index - 1;
	if (numEleToMove != 0)
		memmove(&conditionCourses[index], &conditionCourses[index + 1], sizeof(Course*) * numEleToMove);
	conditionCourses[numOfConditionCourses--] = nullptr;
	return true;
}

bool Course::removeConditionCourse(const char* name)
{
	int index = getConditionCourseIndex(name);
	if (index < 0)
		return false;

	delete conditionCourses[index];
	int numEleToMove = numOfConditionCourses - index - 1;
	if (numEleToMove > 0)
		memmove(&conditionCourses[index], &conditionCourses[index + 1], sizeof(Course*) * numEleToMove);
	conditionCourses[--numOfConditionCourses] = nullptr;

	return true;
}

bool Course::addConditionCourse(const Course& c)
{
	if (numOfConditionCourses >= maxConditionCourses)
		return false;

	if (getConditionCourseIndex(c) >= 0)
		return false;

	conditionCourses[numOfConditionCourses++] = &c;
	return true;
}

bool Course::setLectureWeekDay(const Lecture& lecture, Lecture::eWeekDay day)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	lectures[index]->setWeekDay(day);
	return true;
}

bool Course::setLecturStartHour(const Lecture& lecture, int hour)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	return lectures[index]->setHour(hour);
}

bool Course::setLectureDuration(const Lecture& lecture, int durationHours)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	return lectures[index]->setDuration(durationHours);
}

bool Course::setLectureMaxStudents(const Lecture& lecture, int newMaxStudents)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	return lectures[index]->setMaxStudentsList(newMaxStudents);
}

bool Course::setLectureType(const Lecture& lecture, Lecture::eType type)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	lectures[index]->setLectureType(type);
	return true;
}

// Assumption: classroom is valid
bool Course::setLectureClassroom(const Lecture& lecture, const ClassRoom* classRoom)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;

	lectures[index]->setClassRoom(classRoom);
	return true;
}

// Assumption: professor is valid
bool Course::setLectureLecturer(const Lecture& lecture, const Professor* lecturer)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;

	lectures[index]->setLecturer(*lecturer);
	return true;
}

bool Course::addStudentToWaitingListCourse(const Lecture& lecture, const Student& student)
{
	int index = getLectureIndex(lecture);
	if (index < 0)
		return false;
	return lectures[index]->addToWaitingList(student);
}

// Assumption: student is valid
bool Course::removeStudentToWaitingListCourse(const Lecture& lecture, const Student& student)
{
	int lectureIndex = getLectureIndex(lecture);
	if (lectureIndex < 0)
		return false;

	return lectures[lectureIndex]->removeFromWaitingList(student);
}




Course::eAddingStudentStatus Course::addStudentToCourse(Lecture& lectureToEnter, Student& studentToSign) noexcept(false)
{
	if (getLectureIndex(lectureToEnter) < 0)
		throw "ERROR: Lecture is not in course";

	if (!studentToSign.qualify(*this))
		return Course::eAddingStudentStatus::UNQUALIFIED;

	if (!studentToSign.addLecture(&lectureToEnter))
		return Course::eAddingStudentStatus::FULL;

	return Course::eAddingStudentStatus::SUCCESS;
}

bool Course::notInside(const Student** students, int studentsLen, const Student* isInside) const
{
	for (int i = 0; i < studentsLen; i++)
		if (*(students[i]) == *isInside)
			return false;

	return true;			
}

void Course::printStudentsInCourse(ostream& os) const
{
	Student const *const** studentMat = new const Student *const*[numOfLectures];
	int* studentMatRowSizes = new int[numOfLectures];

	for (int i = 0; i < numOfLectures; i++)
		studentMat[i] = lectures[i]->getStudentList(&studentMatRowSizes[i]);

	int totalStudentsSum = 0;
	for (int i = 0; i < numOfLectures; i++)
		totalStudentsSum += studentMatRowSizes[i];

	const Student** uniqueStudents = new const Student * [totalStudentsSum];

	int uniqueStudentsLen = 0;

	for (int i = 0; i < numOfLectures; i++)
	{
		for (int j = 0; j < studentMatRowSizes[i]; j++)
		{
			if (notInside(uniqueStudents, uniqueStudentsLen, studentMat[i][j]))
			{
				uniqueStudents[uniqueStudentsLen++] = studentMat[i][j];
			}
		}
	}

	for (int i = uniqueStudentsLen; i < totalStudentsSum; i++)
		uniqueStudents[i] = nullptr;

	for (int i = 0; i < uniqueStudentsLen; i++)
		os << *(uniqueStudents[i]);
		
	delete uniqueStudents;
	delete studentMat;
	delete studentMatRowSizes;
}

ostream& operator<<(ostream& os, const Course& c)
{
	for (int i = 0; i < c.numOfLectures; i++)
		os << c.lectures[i];
	return os;
}

Course::~Course()
{
	destroyLectures();
	delete conditionCourses;
	delete name;
}


