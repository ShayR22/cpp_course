#ifndef __H_LECTURE__
#define __H_LECTURE__

#include <ostream>
#include <map>

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
	int maxStudentMap;
	int maxWaitingMap;

	std::map<std::string, const Student*> studentMap;
	std::map<std::string, const Student*> waitingMap;
	
public:
	Lecture(eWeekDay day, int startHour, int duration, eType type, const Course& course,
		    const ClassRoom& classRoom, const Professor& lecturer, const Lecture* practice,
		    int maxStudentMap = 20, int maxWaitingMap = 20) noexcept(false);
	Lecture(const Lecture& otherL) noexcept;

	bool operator==(const Lecture& l) const;
	bool operator==(int id) const;

	Lecture& operator=(const Lecture& otherL) noexcept;

	int getId() const { return id; }
	eWeekDay getWeekDay() const { return this->day; };
	void setWeekDay(eWeekDay day);
	int getHour() const { return this->startHour; };
	bool setHour(int newHour);
	int getDuration() const { return this->duration; };
	bool setDuration(int newDuration);
	int getMaxStudentsMap() const { return this->maxStudentMap; };
	bool setMaxStudentsMap(int newMaxStudentsMap);
	int getMaxWaitingsMap() const { return this->maxWaitingMap; };
	bool setMaxWaitingMap(int newMaxWaitingMap);
	eType getLectureType() const { return this->type; };
	void setLectureType(const eType newType);

	const ClassRoom& getClassRoom() const { return *(this->classRoom); };
	void setClassRoom(const ClassRoom* newClassRoom);

	const Professor& getLecturer()const { return *(this->lecturer); };
	void setLecturer(const Professor& newLectureProfessor);

	const std::map<std::string, const Student*> getStudentMap() const { return this->studentMap; };
	bool addStudent(const Student& newStudent);
	bool removeStudent(const Student& studentToRemove);

	const std::map<std::string, const Student*> getWaitingMap() const { return this->waitingMap; };
	bool addToWaitingMap(const Student& newStudent);
	bool removeFromWaitingMap(const Student& studentToRemove);

	const Lecture& getPracticeLecture() const { return *practice; };
	void setPracticeLecture(const Lecture& newPracticeLecture);
	
	const Course& getCourse() const { return *course; };

	friend std::ostream& operator<<(std::ostream& os, const Lecture& l);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eWeekDay day);
	friend std::ostream& operator<<(std::ostream& os, Lecture::eType type);
};


#endif