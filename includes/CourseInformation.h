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
	CourseInformation(const CourseInformation& otherG);
	
	const Lecture* getLecture() const { return lecture; }
	void setLecture(const Lecture* newLecture);
	int getGrade() const { return grade; }
	bool setGrade(int newGrade);

	CourseInformation& operator=(const CourseInformation& cinfo);
	bool operator==(const CourseInformation& cinfo);
	friend std::ostream& operator<<(std::ostream& os, const CourseInformation& ci);

private:
	CourseInformation(CourseInformation&& otherG) = delete;
	CourseInformation& operator=(CourseInformation&& cinfo) = delete;

};
#endif
