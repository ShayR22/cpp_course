#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "College.h"

#define COURSE_NAME_SIZE 20
#define PERSON_NAME_LEN	20
#define PERSON_ID_LEN	20

using namespace std;

enum class eSystemStatus { QUIT, RESUME};

void cleanBuffer() { while ((getchar()) != '\n'); }

eSystemStatus chooseMenu(College& c);
eSystemStatus chooseStudentsMenu(College& college);
eSystemStatus chooseProfessorsMenu(College& college);
eSystemStatus chooseCoursesMenu(College& college);

// Student menu
Student getStudentInfoFromUser(ostream& errorOs);
Lecture* chooseLectureOfCourseFromUser(College& c);

// Professor menu
Professor getProfessorInfoFromUser(ostream& errorOs);
const char* getProfessorIdFromUser();
void setGradesByUser(College& c, const char* profName, ostream& os);

// Course menu
Course getCourseInfoFromUser(College& college, ostream& os);
const char* getCourseNameFromUser();
Lecture createLecture(College& college, const Course& course, ostream& errorOs);

Person getPersonInfoFromUser(ostream& errorOs);
const char* getStudentIdFromUser();
const char* getPractitionerIdFromUser();

void readCollege()
{
	// TODO
	// ofstream outFile("../college.txt", ios::app);
	ifstream outFile("../college.txt");
}


int main(int argc, char** argv)
{
	College* college = new College();

	//	TODO: load classes from file		////////////////////////////////////////
	//	TODO: load practitioners from file	////////////////////////////////////////

	eSystemStatus choice = eSystemStatus::RESUME;
	do
	{
		choice = chooseMenu(*college);
	} while (choice != eSystemStatus::QUIT);
	cout << "Exit!" << endl;

	return 0;
}

eSystemStatus chooseMenu(College& college)
{
	char choice = '0';

	cout << "\n1. Students menu" << endl;
	cout << "2. Professors menu" << endl;
	cout << "3. Courses menu" << endl;
	cout << "'q' to exit" << endl;
	cin >> choice;

	switch (choice)
	{
	case '1':
		return chooseStudentsMenu(college);
	case '2':
		return chooseProfessorsMenu(college);
	case '3':
		return chooseCoursesMenu(college);
	case 'q':
		return eSystemStatus::QUIT;
	default:
		cout << "Please try again" << endl;
		break;
	}
	return eSystemStatus::RESUME;
}

eSystemStatus chooseStudentsMenu(College& college)
{
	const Student* student;
	Lecture* l;
	const char* studentId;
	char choice = '0';
	
	do
	{
		cout << "\n1. Print all students" << endl;
		cout << "2. Add student to college" << endl;
		cout << "3. Remove student from college" << endl;
		cout << "4. Print student grades" << endl;
		cout << "5. Add student to a course" << endl;
		cout << "6. Print professors of a student" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cleanBuffer();
		cin >> choice;

		switch (choice)
		{
		case '1':
			college.printStudents(cout);
			return eSystemStatus::RESUME;

		case '2':
			if (college.addStudent(getStudentInfoFromUser(cout)))
				cout << "Succeed Add student!" << endl;
			else
				cout << "Failed Add student!" << endl;
			return eSystemStatus::RESUME;

		case '3':
			studentId = getStudentIdFromUser();
			if (college.removeStudent(studentId))
				cout << "Student removed" << endl;
			else
				cout << "Student did not removed" << endl;
			return eSystemStatus::RESUME;

		case '4':
			studentId = getStudentIdFromUser();
			student = college.getStudentById(studentId);
			if (student)
				student->printGrades(cout);
			else
				cout << "No student with ID: " << studentId << " not found!" << endl;
			return eSystemStatus::RESUME;

		case '5':
			studentId = getStudentIdFromUser();
			if (!college.getStudentById(studentId))
			{
				cout << "No student with ID: " << studentId << " not found!" << endl;
				return eSystemStatus::RESUME;
			}

			l = chooseLectureOfCourseFromUser(college);
			if (!l)
			{
				return eSystemStatus::RESUME;
			}

			if ( college.addLectureToStudent(studentId, *l) )
				cout << "Succecfully added" << endl;
			else
				cout << "Error adding" << endl;
			return eSystemStatus::RESUME;

		case '6':
			studentId = getStudentIdFromUser();
			student = college.getStudentById(studentId);
			if (student != nullptr)
				// TODO: implement printProfessorsOfStudent
				// TODO: maybe try/catch is needed
				college.printProfessorsOfStudent(cout, studentId);  
			return eSystemStatus::RESUME;

		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume

		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit

		default:
			cout << "Invalid input: " << choice << endl;
		}
	} while (true);
}

Student getStudentInfoFromUser(ostream& errorOs)
{
	do
	{
		Student::eDepartmenType depEnum;
		int dep;
		Person p = getPersonInfoFromUser(errorOs);
		cout << p << endl;

		cout << "Please choose department:" << endl << "0: Software / 1: Medical / 2: Electricity: ";
		cleanBuffer();
		cin >> dep;
		depEnum = (Student::eDepartmenType)dep;

		try
		{
			Student s(p.getName(), p.getBirthDate(), p.getId(), depEnum);
			cout << "=========================" << endl;
			return s;
		}
		catch (int) {}  // empty catch of student exception (int)  TODO: need to use ostream
	} while (true);
}

Person getPersonInfoFromUser(ostream& errorOs)
{
	char name[PERSON_NAME_LEN];
	char id[PERSON_ID_LEN];
	int day, month, year;
	do
	{
		cout << "Please enter name: ";
		cleanBuffer();
		cin >> name;
		cout << "Please enter id: ";
		cleanBuffer();
		cin >> id;
		cout << "Please enter date (d m y): ";
		cleanBuffer();
		cin >> day >> month >> year;

		Date date(day, month, year);

		try
		{
			return Person(name, date, id);
		}
		catch (const char* msg)
		{
			errorOs << msg << endl;
		}
	} while (true);
}

const char* getStudentIdFromUser()
{
	static char sId[PERSON_ID_LEN];  // TODO: fix it
	cout << "Please enter student ID: ";
	cleanBuffer();
	cin >> sId;
	return sId;
}

Lecture* chooseLectureOfCourseFromUser(College& college)
{
	const char* courseName =  getCourseNameFromUser();
	const Course* course = college.getCourseByName(courseName);
	if (!course)
	{
		cout << "Course not found" << endl;
		return nullptr;
	}

	int numOfLectures = 0;
	Lecture** lectures = course->getLectures(&numOfLectures);
	for (int i = 0; i < numOfLectures; i++)
	{
		cout << (i + 1) << ". " << lectures[i];
	}
	int lIndex;
	cout << "Lecture number: ";
	cleanBuffer();
	cin >> lIndex;
	if (lIndex == 0 || lIndex >= numOfLectures)
	{
		cout << "Invalid choice" << endl;
		return nullptr;
	}
	return lectures[--lIndex];
}

const char* getCourseNameFromUser()
{
	static char name[COURSE_NAME_SIZE];  // TODO: fix it
	cout << "Please enter course name: ";
	cleanBuffer();
	cin >> name;
	return name;
}


eSystemStatus chooseProfessorsMenu(College& college)
{
	const char* professorId;
	const Professor* p;
	char choice = '0';
	do
	{
		cout << "\n1. Print all professors" << endl;
		cout << "2. Add professor to college" << endl;
		cout << "3. Remove professor from college" << endl;
		cout << "4. Print all lectures" << endl;
		cout << "5. Give grades to students" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cleanBuffer();
		cin >> choice;

		switch (choice)
		{
		case '1':
			college.printProfessors(cout);
			return eSystemStatus::RESUME;
		case '2':
			if (college.addProfessor(getProfessorInfoFromUser(cout)))
				cout << "Sucess Adding Professor!" << endl;
			else
				cout << "Failed Adding Professor!" << endl;
			return eSystemStatus::RESUME;
		case '3':
			cout << "Removing Professor\n";
			professorId = getProfessorIdFromUser();
			if (college.removeProfessor(professorId))
				cout << "Professor removed";
			else
				cout << "Professor did not removed\n";
			return eSystemStatus::RESUME;
		case '4':
			professorId = getProfessorIdFromUser();
			p = college.getPractitionerById(professorId);
			if (p != nullptr)
				p->printLectures(cout);
			return eSystemStatus::RESUME;
		case '5':
			professorId = getProfessorIdFromUser();
			setGradesByUser(college, professorId, cout);
			return eSystemStatus::RESUME;
		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume
		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit
		default:
			cout << "Invalid input: " << choice << endl;
		}
	} while (true);
}

Professor getProfessorInfoFromUser(ostream& errorOs)
{
	do
	{
		Person p = getPersonInfoFromUser(errorOs);

		double salary;
		cout << "\nPlease enter salary: ";
		cleanBuffer();
		cin >> salary;
		try
		{
			return Professor(p.getName(), p.getBirthDate(), p.getId(), salary);
		}
		catch (int) {}  // TODO: change the catch
	} while (true);
}

const char* getProfessorIdFromUser()
{
	static char profId[PERSON_ID_LEN];  // TODO: fix it
	cout << "\nPlease enter student ID: ";
	cleanBuffer();
	cin >> profId;
	return profId;
}

void setGradesByUser(College& college, const char* profName, ostream& os)
{
	char courseName[COURSE_NAME_SIZE];
	int lectureId;
	int numOfLectures = 0;
	const Lecture*const* arr = college.getProfessorById(profName)->getLectures(&numOfLectures);
	
	college.getProfessorById(profName)->printLectures(os);

	// TODO: maybe the user don't need to enter the course name. do it more simple
	cout << "\nPlease enter Course Name: ";
	cleanBuffer();
	cin >> courseName;
	const Course* course = college.getCourseByName(courseName);
	if (course == nullptr)
		return;

	cout << "\nPlease enter lecture ID (of " << courseName << "): ";
	cleanBuffer();
	cin >> lectureId;
	const Lecture* lecture = course->getLectureById(lectureId);
	if (lecture == nullptr)
		return;

	int studentListSize = 0;
	const Student*const* studentList = lecture->getStudentList(&studentListSize);

	int grade = 0;
	for (int i = 0; i < studentListSize; i++)
	{
		cout << studentList[i] << ", Please enter grade: ";
		cleanBuffer();
		cin >> grade;
		college.updateStudentGrade(studentList[i]->getId(), *lecture, grade);
	}
}


eSystemStatus chooseCoursesMenu(College& college)
{
	const Course* course = nullptr;
	const char* courseName;
	char choice = '0';
	do
	{
		cout << "1. Print all courses" << endl;
		cout << "2. Create new course" << endl;
		cout << "3. Delete course" << endl;
		cout << "4. Add new lecture to course" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cleanBuffer();
		cin >> choice;

		switch (choice)
		{
		case '1':
			college.printCourses(cout);
			return eSystemStatus::RESUME;
		case '2':
			course = &getCourseInfoFromUser(college, cout);
			college.addCourse(*course);
			return eSystemStatus::RESUME;
		case '3':
			// TODO: maybe to create a new college func: removeCourse(courseName)
			courseName = getCourseNameFromUser();
			course = college.getCourseByName(courseName);
			if (course != nullptr)
				college.removeCourse(*course);
			return eSystemStatus::RESUME;
		case '4':
			courseName = getCourseNameFromUser();
			course = college.getCourseByName(courseName);
			if (course != nullptr)
				college.addNewLectureToCourse(courseName, createLecture(college, *course, cout));
			return eSystemStatus::RESUME;
		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume
		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit
		default:
			break;
		}
	} while (true);
}

Course getCourseInfoFromUser(College& college, ostream& errorOs)
{
	do
	{
		char courseName[COURSE_NAME_SIZE];
		float points;

		cout << "Please enter course name: ";
		cleanBuffer();
		cin >> courseName;
		cout << "Please enter number of points: ";
		cleanBuffer();
		cin >> points;
		const char* profId = getProfessorIdFromUser();
		const Professor* coordinator = college.getProfessorById(profId);

		try
		{
			return Course(courseName, coordinator, points);
		}
		catch (const char* msg)
		{
			errorOs << msg << endl;
		}
	} while (true);
}

Lecture createLecture(College& college, const Course& course, ostream& errorOs)
{
	Lecture::eType lectureType = (Lecture::eType)1;
	Lecture::eWeekDay lectureDay;
	int lecDay, lectureStartHour, lectureDuration, lectureRoomNumber;
	int pracDay, pracStartHour, pracDuration, pracRoomNumber;

	const char* profId;
	const char* practitionerId;

	const ClassRoom* lectureRoom;
	const ClassRoom* pracRoom;
	const Practitioner* practiceProf;
	const Professor* lectureProf;

	do
		{
		cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
		cleanBuffer();
		cin >> lecDay;
		lectureDay = (Lecture::eWeekDay)lecDay;
		cout << "Please enter lecture start hour: ";
		cleanBuffer();
		cin >> lectureStartHour;
		cout << "Please enter lecture duration: ";
		cleanBuffer();
		cin >> lectureDuration;
		cout << "Please enter lecture classroom number: ";
		cleanBuffer();
		cin >> lectureRoomNumber;
		lectureRoom = college.getClassRoomByNumber(lectureRoomNumber);

		profId = getProfessorIdFromUser();
		lectureProf = college.getProfessorById(profId);
		if (!lectureProf)
		{
			cout << "Can not find proffesor";
			continue;
		}

		Lecture::eType pracType = (Lecture::eType)0;
		Lecture::eWeekDay practiceDay;

		cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
		cin >> pracDay;
		practiceDay = (Lecture::eWeekDay)pracDay;
		cout << "Please enter lecture start hour: ";
		cin >> pracStartHour;
		cout << "Please enter lecture duration: ";
		cin >> pracDuration;
		cout << "Please enter lecture classroom number: ";
		cin >> pracRoomNumber;
		pracRoom = college.getClassRoomByNumber(lectureRoomNumber);

		practitionerId = getPractitionerIdFromUser();
		practiceProf = college.getPractitionerById(practitionerId);
		if (!practiceProf)
		{
			cout << "Can not find proffesor!\n";
			continue;
		}

		try
		{
			// TODO: ask shay why course in lecture is not const?
			return Lecture(practiceDay, pracStartHour, pracDuration, pracType,
				course, *pracRoom, *practiceProf, nullptr);
		}
		catch (const char* msg)
		{
			errorOs << msg << endl;
		}
	} while (true);
}

const char* getPractitionerIdFromUser()
{
	static char practId[PERSON_ID_LEN];  // TODO: fix it
	cout << "Please enter practitioner ID: ";
	cleanBuffer();
	cin >> practId;
	return practId;
}


