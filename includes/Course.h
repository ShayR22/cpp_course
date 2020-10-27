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

	void destroyLectures();

	int getLectureIndex(int id) const;
	int getLectureIndex(const Lecture& l) const;
	int getConditionCourseIndex(const char* name) const;
	int getConditionCourseIndex(const Course& c) const;
	bool notInside(const Student** student, int studentsLen, const Student* isInside) const;

	bool checkIfHourOverlap(const Lecture& lecture, const Lecture& practice);

public:
	Course(const char* name, const Professor* coordinator, float points = 0.5, int maxLectures = 20, int maxConditionCourses = 20);
	Course(const Course& other) noexcept;
	Course(Course&& other) noexcept;

	Course& operator=(const Course& other);
	Course& operator=(Course&& other) noexcept;

	bool operator==(const Course& other) const;
	bool operator==(const char *name) const;

	const char* getCourseName() const { return name; }
	bool setCourseName(const char* name);
	const Professor* getCoordinator()const { return coordinator; }
	bool setCoordinator(const Professor* p);
	float getPoints() const { return points; }
	bool setPoints(float p);
	inline Lecture** getLectures(int* numOfLectures) const;
	bool removeLecture(const Lecture& lectureToRemove);
	bool removeLecture(int id);
	bool addLecture(const Lecture& lectureToAdd);
	inline const Course** getConditionsCourses(int* numOfConditionCourses) const;
	bool removeConditionCourse(const Course& c);
	bool removeConditionCourse(const char* name);
	bool addConditionCourse(const Course& c);
	const Lecture* getLectureById(int lectureId) const;

	bool setLectureWeekDay(const Lecture& lecture, Lecture::eWeekDay day);
	bool setLecturStartHour(const Lecture& lecture, int hour);
	bool setLectureDuration(const Lecture& lecture, int durationHours);
	bool setLectureMaxStudents(const Lecture& lecture, int newMaxStudents);
	bool setLectureType(const Lecture& lecture, Lecture::eType type);
	bool setLectureClassroom(const Lecture& lecture, const ClassRoom* classRoom);
	bool setLectureLecturer(const Lecture& lecture, const Professor* lecturer);
	bool addStudentToWaitingListCourse(const Lecture& lecture, const Student& student);
	bool removeStudentToWaitingListCourse(const Lecture& lecture, const Student& student);
	bool setLecturePractice(int lectureID, int practiceID);

	eAddingStudentStatus addStudentToCourse(const Lecture& lectureToEnter, Student& studentToSign) noexcept(false);
	
	void printStudentsInCourse(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Course& c);

	~Course();
};

Lecture** Course::getLectures(int* numOfLectures) const
{
	*numOfLectures = this->numOfLectures;
	return lectures;
}

const Course** Course::getConditionsCourses(int* numOfConditionCourses) const
{
	*numOfConditionCourses = this->numOfConditionCourses;
	return conditionCourses;
}

#endif /* __H_COURSE__ */
