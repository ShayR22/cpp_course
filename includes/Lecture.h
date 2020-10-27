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
	inline eWeekDay getWeekDay() const;
	void setWeekDay(eWeekDay day);
	inline int getHour() const;
	bool setHour(int newHour);
	inline int getDuration() const;
	bool setDuration(int newDuration);
	inline int getMaxStudentsList() const;
	bool setMaxStudentsList(int newMaxStudentsList);
	inline int getMaxWaitingsList() const;
	bool setMaxWaitingList(int newMaxWaitingList);
	inline eType getLectureType()const;
	void setLectureType(const eType newType);

	inline const ClassRoom& getClassRoom() const;
	void setClassRoom(const ClassRoom* newClassRoom);

	inline const Professor& getLecturer()const;
	void setLecturer(const Professor& newLectureProfessor);

	inline const Student*const* getStudentList(int* numOfStudentList) const;
	bool addStudent(const Student& newStudent);
	bool removeStudent(Student& studentToRemove);

	inline const Student*const* getWaitingList(int* numOfWaitingList)const;
	bool addToWaitingList(const Student& newStudent);
	bool removeFromWaitingList(const Student& studentToRemove);

	inline const Lecture& getPracticeLecture() const;
	void setPracticeLecture(const Lecture& newPracticeLecture);
	
	inline const Course& getCourse()const;

	friend std::ostream& operator<<(std::ostream& os, const Lecture& l);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eWeekDay day);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eType type);

	~Lecture();
};

Lecture::eWeekDay Lecture::getWeekDay() const
{
	return this->day;
}

int Lecture::getHour() const
{
	return this->startHour;
}

int Lecture::getDuration() const
{
	return this->duration;
}

const Professor& Lecture::getLecturer() const
{
	return *(this->lecturer);
}

const Student* const* Lecture::getStudentList(int* numOfStudentList) const
{
	*numOfStudentList = this->numOfStudentList;
	return this->studentList;
}

Lecture::eType Lecture::getLectureType() const
{
	return this->type;
}

const ClassRoom& Lecture::getClassRoom() const
{
	return *(this->classRoom);
}

const Course& Lecture::getCourse() const
{
	return *course;
}

#endif