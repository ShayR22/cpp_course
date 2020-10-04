#include "CourseInformation.h"
#include "Lecture.h"


CourseInformation::CourseInformation(const Lecture* lecture, int grade) :
	lecture(lecture), grade(grade)
{

}


void CourseInformation::setLecture(const Lecture* newLecture)
{
	lecture = newLecture;
}

bool CourseInformation::setGrade(int newGrade)
{
	if (newGrade < 1 || newGrade > 100)
		return false;
	grade = newGrade;
	return true;
}


void CourseInformation::print() const
{

}
