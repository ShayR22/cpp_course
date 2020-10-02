#include <ostream>
#include "Course.h"

using namespace std;

Course::Course(const char* name, Professor& coordinator, float points,
	int maxLectures, int maxConditionCourses) : coordinator(coordinator)
{

}

Course::Course(Course&& otherC) : coordinator(otherC.coordinator)
{

}

bool Course::setCourseName(const char* newCourseName)
{
	return false;
}

bool Course::setCoordinator(const Professor& p)
{
	return false;
}

bool Course::setPoints(float p)
{
	return false;
}

Lecture** Course::getLectures(int* numOfLectures) const
{
	return nullptr;

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


