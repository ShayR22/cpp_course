#ifndef __H_GRADE__
#define __H_GRADE__

#include "Lecture.h"

class CourseInformation
{
private:
	const Lecture* lecture;
	int grade;
public:
	CourseInformation(const Lecture* lecture, int grade = -1);

	const Lecture* getLecture() const { return lecture; }
	void setLecture(const Lecture* newLecture);
	int getGrade() const { return grade; }
	bool setGrade(int newGrade);

	friend std::ostream& operator<<(std::ostream& os, const CourseInformation& ci);

private:
	CourseInformation(const CourseInformation& otherG) = delete;
	CourseInformation(CourseInformation&& otherG) = delete;
	CourseInformation& operator=(const CourseInformation& cinfo) = delete;
	CourseInformation& operator=(CourseInformation&& cinfo) = delete;
};


#endif
