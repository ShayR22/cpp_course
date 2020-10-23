#include "CourseInformation.h"
#include "Lecture.h"
#include "Course.h"

using namespace std;

CourseInformation::CourseInformation(const Lecture* lecture, int grade) :
	lecture(lecture), grade(grade) {}

CourseInformation::CourseInformation(const CourseInformation& otherG) :
	lecture(otherG.lecture), grade(otherG.grade){}

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

CourseInformation& CourseInformation::operator=(const CourseInformation& cinfo)
{
	this->lecture = cinfo.lecture;
	this->grade = cinfo.grade;

	return *this;
}

bool CourseInformation::operator==(const CourseInformation& cinfo)
{
	return *(this->lecture) == *(cinfo.lecture);
}

ostream& operator<<(ostream& os, const CourseInformation& ci)
{
	os << "Course: " << ci.lecture->getCourse().getCourseName() << ", Grade: " << ci.grade << endl;
	return os;
}
