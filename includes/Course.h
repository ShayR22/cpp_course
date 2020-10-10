#ifndef __H_COURSE__
#define __H_COURSE__

#include "Lecture.h"

class Course
{
public:
	enum class eAddingStudentStatus { SUCCESS, UNQUALIFIED, FULL };// for lecture
private:
	char* name;
	const Professor* coordinator;
	float points;
	Lecture** lectures;
	int maxLectures;
	int numOfLectures;
	const Course** conditionCourses;
	int maxConditionCourses;
	int numOfConditionCourses;
	inline bool isNearlyEqual(double x, double y);

	void destroyLectures();

	int getLectureIndex(const Lecture& l);
	int getConditionCourseIndex(const Course& c);
	bool notInside(const Student** student, int studentsLen, const Student* isInside) const;

public:
	Course(const char* name, const Professor* coordinator, float points = 0.5, int maxLectures = 20, int maxConditionCourses = 20);
	Course(const Course& other) noexcept;
	Course(Course&& other) noexcept;

	Course& operator=(const Course& other);
	Course& operator=(Course&& other) noexcept;

	bool operator==(const Course& other) const;
	bool operator==(const char *name) const;


	const char* getCourseName() const { return name; }
	bool setCourseName(const char* newCourseName);
	const Professor* getCoordinator()const { return coordinator; }
	bool setCoordinator(const Professor* p);
	float getPoints() const { return points; }
	bool setPoints(float p);
	Lecture** getLectures(int* numOfLectures) const;
	bool removeLecture(const Lecture& lectureToRemove);
	bool addLecture(const Lecture& lectureToAdd);
	const Course** getConditionsCourses(int* numOfConditionCourses) const;
	bool removeConditionCourse(const Course& c);
	bool addConditionCourse(const Course& c);

	eAddingStudentStatus addStudentToCourse(Lecture& lectureToEnter, Student& studentToSign) noexcept(false);
	
	void printStudentsInCourse(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Course& c);

	~Course();
};

#endif /* __H_COURSE__ */
