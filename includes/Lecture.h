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
	enum eWeekDay { SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY };
	enum eType { PRACTICE = 0, LECTURE };

private:
	int id;		//  =  ++auromaticID
	eWeekDay day;
	int startHour;
	int duration;
	eType type;
	Course& course;
	const ClassRoom* classRoom;
	const Professor* lecturer;
	const Lecture* practice;//tirgul
	Student** studentList;
	int maxStudentList;
	int numOfStudentList;
	const Student** waitingList;
	int maxWaitingList;
	int numOfWaitingList;
	

public:
	/******Constructors******/
	Lecture(eWeekDay day, int startHour, int duration, eType type, Course& course,
		    const ClassRoom& classRoom, const Professor& lecturer, Lecture* practice,
		    int maxStudentList = 20, int maxWaitingList = 20);
	Lecture(const Lecture& otherL);

	bool operator==(const Lecture& l) const;
	bool operator==(int id) const { return this->id == id; }

	//Lecture(Lecture&& otherL);
	Lecture& operator=(const Lecture& otherL);
	Lecture& operator=(Lecture&& otherL);

	/******Gets/Sets******/
	int getId() const { return id; }
	eWeekDay getWeekDay()const { return day; }
	bool setWeekDay(eWeekDay day);
	int getHour() const { return startHour; }
	bool setHour(int newHour);
	int getDuration()const { return duration; }
	bool setDuration(int newDuration);
	int getMaxStudentsList()const { return maxStudentList; }
	bool setMaxStudentsList(int newMaxStudentsList); //Check that: "ClassRoom->maxSeats >= newMaxStudentList" 
	eType getLectureType()const { return type; }
	bool setLectureType(const eType newType);

	const ClassRoom& getClassRoom() const { return *classRoom; }
	bool setClassRoom(const ClassRoom* newClassRoom);

	const Professor& getLecturer()const { return *lecturer; }
	bool setLecturer(const Professor& newLectureProfessor);

	const Student** getStudentList(int* numOfStudentList) const; // returning also the "current number of students"
	bool addStudent(const Student& newStudent);
	bool removeStudent(Student& studentToRemove);

	const Student** getWaitingList(int* numOfWaitingList)const; // returning also the "current number of students"
	bool addToWaitingList(const Student& newStudent);
	bool removeFromWaitingList(const Student& studentToRemove);

	const Lecture& getPracticeLecture() const { return *practice; }
	bool setPracticeLecture(const Lecture& newPracticeLecture);
	
	const Course& getCourse()const { return course; }

	friend std::ostream& operator<<(std::ostream& os, const Lecture& l);

	/******Deconstructor******/
	~Lecture();

};

#endif