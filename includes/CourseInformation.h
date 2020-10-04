#ifndef __H_GRADE__
#define __H_GRADE__

class Lecture;

class CourseInformation
{
private:
	/******Attributes******/
	Lecture& lecture;
	int grade;
public:
	/******Constructors******/
	CourseInformation(Lecture& lecture, int grade = -1);


	/******Gets/Sets******/
	const Lecture& getLecture() const { return lecture; }
	bool setLecture(const Lecture& newLecture);
	int getGrade() const { return grade; }
	bool setGrade(int newGrade);

	/******print******/
	void print()const;

private:
	/******Constructors******/
	CourseInformation(const CourseInformation& otherG) = delete;
	CourseInformation(CourseInformation&& otherG) = delete;
	CourseInformation& operator=(const CourseInformation& cinfo) = delete;
	CourseInformation& operator=(CourseInformation&& cinfo) = delete;
};
#endif
