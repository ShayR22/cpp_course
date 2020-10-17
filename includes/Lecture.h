#ifndef __H_LECTURE__
#define __H_LECTURE__

#include <ostream>

class Student;
class Professor;
class ClassRoom;
class Course;

class Lecture
{
private:
	static int automaticID;

public:
	enum class eWeekDay { SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY};
	enum class eType { PRACTICE = 0, LECTURE };

private:
	int id;	
	eWeekDay day;
	int startHour;
	int duration;
	eType type;
	const Course* course;
	const ClassRoom* classRoom;
	const Professor* lecturer;
	const Lecture* practice;
	const Student** studentList;
	int maxStudentList;
	int numOfStudentList;
	const Student** waitingList;
	int maxWaitingList;
	int numOfWaitingList;

	void removeStudentByIndex(int index, const Student** ptrArray, int arraySize);
	
public:
	Lecture(eWeekDay day, int startHour, int duration, eType type, const Course& course,
		    const ClassRoom& classRoom, const Professor& lecturer, const Lecture* practice,
		    int maxStudentList = 20, int maxWaitingList = 20) noexcept(false);
	Lecture(const Lecture& otherL) noexcept;
	Lecture(Lecture&& otherL) noexcept;

	bool operator==(const Lecture& l) const;
	bool operator==(int id) const;

	Lecture& operator=(const Lecture& otherL) noexcept;
	Lecture& operator=(Lecture&& otherL) noexcept;

	int getId() const { return id; }
	eWeekDay getWeekDay() const;
	void setWeekDay(eWeekDay day);
	int getHour() const;
	bool setHour(int newHour);
	int getDuration() const;
	bool setDuration(int newDuration);
	int getMaxStudentsList() const;
	bool setMaxStudentsList(int newMaxStudentsList);
	int getMaxWaitingsList() const;
	bool setMaxWaitingList(int newMaxWaitingList);
	eType getLectureType()const;
	void setLectureType(const eType newType);

	const ClassRoom& getClassRoom() const;
	void setClassRoom(const ClassRoom* newClassRoom);

	const Professor& getLecturer()const;
	void setLecturer(const Professor& newLectureProfessor);

	const Student*const* getStudentList(int* numOfStudentList) const;
	bool addStudent(const Student& newStudent);
	bool removeStudent(Student& studentToRemove);

	const Student*const* getWaitingList(int* numOfWaitingList)const;
	bool addToWaitingList(const Student& newStudent);
	bool removeFromWaitingList(const Student& studentToRemove);

	const Lecture& getPracticeLecture() const;
	void setPracticeLecture(const Lecture& newPracticeLecture);
	
	const Course& getCourse()const;

	friend std::ostream& operator<<(std::ostream& os, const Lecture& l);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eWeekDay day);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eType type);

	~Lecture();
};

#endif