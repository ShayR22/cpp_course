#define _CRT_SECURE_NO_WARNINGS
#define EPSSILON 0.0000001


#include <ostream>
#include <string>
#include <cmath>
#include "Course.h"


using namespace std;

Course::Course(const char* name, Professor& coordinator, float points,
	int maxLectures, int maxConditionCourses) : 
	coordinator(coordinator), points(points), maxLectures(maxLectures), maxConditionCourses(maxConditionCourses)
{
	strncpy(this->name, name, Course::COURSE_NAME_SIZE);
	this->name[Course::COURSE_NAME_SIZE - 1] = '\0';

	this->lectures = new Lecture * [maxLectures];
	this->numOfLectures = 0;

	this->conditionCourses = new Course * [maxConditionCourses];
	this->numOfConditionCourses = 0;
}

Course::Course(Course&& otherC) noexcept :
	coordinator(otherC.coordinator), points(otherC.points),
	maxLectures(otherC.maxLectures), lectures(otherC.lectures), numOfLectures(otherC.numOfLectures),
	maxConditionCourses(otherC.maxConditionCourses), conditionCourses(otherC.conditionCourses),
	numOfConditionCourses(otherC.numOfConditionCourses)
{
	/* TODO maybe change the way the class work to have char * instead static char [] */
	strncpy(name, otherC.name, Course::COURSE_NAME_SIZE);

	otherC.lectures = nullptr;
	otherC.maxLectures = 0;
	otherC.numOfLectures = 0;

	otherC.conditionCourses = nullptr;
	otherC.maxConditionCourses = 0;
	otherC.numOfConditionCourses = 0;
}

bool Course::setCourseName(const char* newCourseName)
{
	if (strlen(newCourseName) >= Course::COURSE_NAME_SIZE)
		return false;

	strncpy(name, newCourseName, Course::COURSE_NAME_SIZE);

}

bool Course::setCoordinator(const Professor& p)
{
	/* in order to implement this we would require operator = for proffesor*/
	return false;
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
	*numOfLectures = numOfLectures;
	return lectures;
}

// returning also the current number of lectures
bool Course::removeLecture(const Lecture& lectureToRemove)
{
	return false;
}

bool Course::addLecture(const Lecture& lectureToAdd)
{
	return false;
}

const Course** Course::getConditionsCourses(int* numOfConditionsCourses) const
{
	return nullptr;
}

// returning also the current number of courses
bool Course::removeConditionCourse(const Course& c)
{
	return false;
}

bool Course::addConditionCourse(const Course& c)
{
	return false;
}

Course::eAddingStudentStatus Course::addStudentToCourse(Lecture& lecture_to_enter, Student& student_to_sign)
{
	return Course::eAddingStudentStatus::UNQUALIFIED;
}

void Course::printStudentsInCourse() const
{

}

ostream& operator<<(ostream& os, const Course& c)
{
	return os;
}

Course::~Course()
{

}


