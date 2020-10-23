#include "CourseInformation.h"
#include "Lecture.h"

using namespace std;

CourseInformation::CourseInformation(const Lecture* lecture, int grade) :
	lecture(lecture), grade(grade) {}


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

ostream& operator<<(ostream& os, const CourseInformation& ci)
{
	os << "Lecture Info: " << endl;
	os << *(ci.lecture);
	os << "Grade: " << ci.grade << endl;
	return os;
}
