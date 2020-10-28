#ifndef __H_COURSE__
#define __H_COURSE__

#include "Lecture.h"
#include <map>

class Course
{
public:
	enum class eAddingStudentStatus { SUCCESS, UNQUALIFIED, FULL };// for lecture
private:
	std::string name;
	const Professor* coordinator;
	float points;
	std::map<int, Lecture*> lectures;
	int maxLectures;
	std::map<std::string, const Course*> conditionCourses;
	int maxConditionCourses;

	bool checkIfHourOverlap(const Lecture& lecture, const Lecture& practice);

public:
	Course(const std::string& name, const Professor* coordinator, float points = 0.5, int maxLectures = 20, int maxConditionCourses = 20);
	Course(const Course& other) noexcept;
	Course(Course&& other) noexcept;

	Course& operator=(const Course& other) noexcept;
	Course& operator=(Course&& other) noexcept; 

	bool operator==(const Course& other) const;
	bool operator==(const std::string& name) const;

	const std::string& getCourseName() const { return name; }
	bool setCourseName(const std::string& newCourseName);
	const Professor* getCoordinator()const { return coordinator; }
	bool setCoordinator(const Professor* p);
	float getPoints() const { return points; }
	bool setPoints(float p);
	std::map<int, Lecture*> getLectures() const { return lectures; };
	bool removeLecture(const Lecture& lectureToRemove);
	bool removeLecture(int id);
	bool addLecture(const Lecture& lectureToAdd);
	const std::map<std::string, const Course*> getConditionsCourses() const { return conditionCourses; };
	bool removeConditionCourse(const Course& c);
	bool removeConditionCourse(const std::string& name);
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
	bool removeStudentFromCourse(const Student& student);

	eAddingStudentStatus addStudentToCourse(const Lecture& lectureToEnter, Student& studentToSign) noexcept(false);
	
	void printStudentsInCourse(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Course& c);

	~Course();
};

#endif /* __H_COURSE__ */
