#ifndef __H_COURSE__
#define __H_COURSE__

#include "Lecture.h"

class Course
{
public:
	enum eAddingStudentStatus { SUCCESS, UNQUALIFIED, FULL };// for lecture
	static const int COURSE_NAME_SIZE = 20;
private:
	/******Attributes******/
	char name[COURSE_NAME_SIZE];
	Professor& coordinator;
	float points;
	Lecture** lectures;
	int maxLectures;
	int numOfLectures;
	Course** conditionCourses;
	int maxConditionCourses;
	int numOfConditionCourses;

public:
	/******Constructors******/
	Course(const char* name, const Professor& coordinator, float points = 0.5, int maxLectures = 20, int maxConditionCourses = 20);
	Course(Course&& otherC);

	/******Gets/Sets******/
	const char* getCourseName() const { return name; }
	bool setCourseName(const char* newCourseName);
	const Professor& getCoordinator()const { return coordinator; }
	bool setCoordinator(const Professor& p);
	float getPoints() const { return points; }
	bool setPoints(float p);
	Lecture** getLectures(int* numOfLectures) const; // returning also the current number of lectures
	bool removeLecture(const Lecture& lectureToRemove);
	bool addLecture(const Lecture& lectureToAdd);
	const Course** getConditionsCourses(int* numOfConditionsCourses) const; // returning also the current number of courses
	bool removeConditionCourse(const Course& c);
	bool addConditionCourse(const Course& c);

	eAddingStudentStatus addStudentToCourse(Lecture& lecture_to_enter, Student& student_to_sign);//check qualification's conditions, 
	//searching the lecture, and adding 
	
	/******print******/
	void printStudentsInCourse() const;
	friend ostream& operator<<(ostream& os, const Course& c);

	/******Deconstructor******/
	~Course();

private:
	/******Constructors******/
	Course(const Course& otherC) = delete;
	Course& operator=(const Course& otherC) = delete;
	Course& operator=(Course&& otherC) = delete;
};


#endif
