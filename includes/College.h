#ifndef __H_COLLEGE__
#define __H_COLLEGE__

#include "Course.h"
#include "Person.h"
#include "Practitioner.h" // need to check where put this include

class College
{
private:
	/******Attributes******/
	Student** students;
	int maxStudents;
	int numOfStudents;
	Professor** professors;
	int maxProfessors;
	int numOfProfessors;
	Practitioner** practitioners;
	int maxPractitioners;
	int numOfPractitioners;
	Course** courses;
	int maxCourses;
	int numOfCourses;
	ClassRoom** classRooms;
	int maxClassRooms;
	int numOfClassRooms;

public:
	/******Constructors******/
	College(int maxAllStudents = 100, int maxAllProfessors = 100, int maxAllCourses = 100, int maxAllClassRooms = 100);

	/******Gets/Sets******/
	Student** getStudents(int* numOfStudents)const; // return also the current number of students
	bool addStudent(const Student& newStudent);
	bool removeStudent(const Student& studentToRemove);
	Student* getStudentById(const char* id);

	Practitioner** getPractitioners(int* numOfPractitioners)const; // return also the current number of professors
	bool addPractitioner(const Professor& newPractitioner);
	bool removePractitioner(const Professor& practitionerToRemove);
	Practitioner* getPractitionerById(const char* id);

	Professor** getProfessors(int* numOfProfessors)const; // return also the current number of professors
	bool addProfessor(const Professor& newProfessor);
	bool removeProfessor(const Professor& professorToRemove);
	Professor* getProfessorById(const char* id);

	Course** getCourses(int* numOfCourses) const; // return also the current number of courses
	bool addCourse(const Course& newCourse);
	bool removeCourse(const Course& courseToRemove);
	Course* getCourseByName(const char* name);
	bool addNewLectureToCourse(const Lecture& newLecture, const Course& course);

	const ClassRoom** getClassRooms(int* numOfClassRooms); // return also the current number of ClassRooms
	bool addClassRoom(const ClassRoom& newClassroom);
	bool removeClassRoom(const ClassRoom& classRoomToRemove);
	ClassRoom* getClassRoomByNumber(int number);


	const College& operator+=(const Course& c);		//	use college.addCourse
	const College& operator+=(const Student& s);	//	use college.addStudent
	const College& operator+=(const Professor& p);	//	use college.addProfessor
	const College& operator+=(const Practitioner& p);	//	use college.addPractitioner
	const College& operator+=(const ClassRoom& cr);		//	use college.addClassRoom

	const College& operator-=(const ClassRoom& cr);		//	use college.removeClassRoom

	/******Deconstructor******/
	~College();

private:
	/******Constructors******/
	College(const College& otherC) = delete;
	College(College&& otherC) = delete;
	College& operator=(const College& otherC) = delete;
	College& operator=(College&& otherC) = delete;
};
#endif
