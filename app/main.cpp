#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "College.h"

#define COURSE_NAME_SIZE 20
#define PERSON_NAME_LEN	20
#define PERSON_ID_LEN	20

using namespace std;

char printMenu(College& college);
char printStudentsMenu(College& college);
char printProfessorsMenu(College& college);
char printCoursesMenu(College& college);

void printArray(const void** arr, int size);
Person* getPersonInfo();

void printStudents(College& c);
Student* getStudentById(College& c);
Student* getStudentInfo();
Lecture* chooseLectureOfCourse(College& c);
Lecture* createLecture(College& college, Course& course);
void printProfessors(College& c);
Professor* getProfessorById(College& c);
Practitioner* getPractitionerById(College& c);
Professor* getProfessorInfo();
void printCourses(College& c);
Course& getCourseInfo(College& college);
Course* getCourseByName(College& c);
void setGrades(College& c, Professor& prof);

int main(int argc, char** argv)
{
	College* college = new College();

	//	TODO: load classes from file		////////////////////////////////////////
	//	TODO: load practitioners from file	////////////////////////////////////////

	char choice = '0';
	do
	{
		choice = printMenu(*college);
	} while (choice != 'q');

	return 0;
}

char printMenu(College& college)
{
	char choice = '0';

	cout << "1. Students menu" << endl;
	cout << "2. Professors menu" << endl;
	cout << "3. Courses menu" << endl;
	cout << "'q' to exit" << endl;

	switch (choice)
	{
	case '1':
		return printStudentsMenu(college);
	case '2':
		return printProfessorsMenu(college);
	case '3':
		return printCoursesMenu(college);
	case 'q':
		return 'q';
	default:
		cout << "Please try again" << endl;
		break;
	}
	return 'q';
}

char printStudentsMenu(College& college)
{
	Student* s;
	Lecture* l;
	char choice = '0';
	do
	{
		cout << "1. Print all students" << endl;
		cout << "2. Add student to college" << endl;
		cout << "3. Remove student from college" << endl;
		cout << "4. Print student grades" << endl;
		cout << "5. Add student to a course" << endl;
		cout << "6. Print professors of a student" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			printStudents(college);
			return 'r';
		case '2':
			college.addStudent(*getStudentInfo());
			return 'r';
		case '3':
			if (college.removeStudent(*getStudentById(college)))
				cout << "Student removed" << endl;
			else
				cout << "Student did not removed" << endl;
			return 'r';
		case '4':
			s = getStudentById(college);
			s->printGrades(cout);
			return 'r';
		case '5':
			 s = getStudentById(college);
			if (!s)
				return 'r';
			l = chooseLectureOfCourse(college);
			if (!l)
				return 'r';
			if (s->addLecture(chooseLectureOfCourse(college)))
				cout << "Succecfully added" << endl;
			else
				cout << "Error adding" << endl;
			return 'r';
		case '6':
			s = getStudentById(college);
			if (s)
				s->printProfessores(cout);
			return 'r';
		case 'r':
			return 'r'; // return to main menu and resume
		case 'q':
			return 'q';	// return to main menu and exit
		default:
			break;
		}
	} while (choice != 'q');
	return 'q';
}


char printProfessorsMenu(College& college)
{
	Professor* p;
	char choice = '0';
	do
	{
		cout << "1. Print all professors" << endl;
		cout << "2. Add professor to college" << endl;
		cout << "3. Remove professor from college" << endl;
		cout << "4. Print all lectures" << endl;
		cout << "5. Give grades to students" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			printProfessors(college);
			return 'r';
		case '2':
			college.addProfessor(*getProfessorInfo());
			return 'r';
		case '3':
			cout << "Removing Professor" << endl;
			if (college.removeProfessor(*getProfessorById(college)))
				cout << "Professor removed";
			else
				cout << "Professor did not removed";
			return 'r';
		case '4':
			p = getProfessorById(college);
			if (p)
				p->printLectures(cout);
			return 'r';
		case '5':
			setGrades(college, *getProfessorById(college));
			return 'r';
		case 'r':
			return 'r'; // return to main menu and resume
		case 'q':
			return 'q';	// return to main menu and exit
		default:
			break;
		}
	} while (choice != 'q');
	return 'q';
}


char printCoursesMenu(College& college)
{
	Course* course = nullptr;
	char choice = '0';
	do
	{
		cout << "1. Print all courses" << endl;
		cout << "2. Create new course" << endl;
		cout << "3. Delete course" << endl;
		cout << "4. Add new lecture to course" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			printCourses(college);
			return 'r';
		case '2':
			college.addCourse(getCourseInfo(college));
			return 'r';
		case '3':
			college.removeCourse(*getCourseByName(college));
		case '4':
			course = getCourseByName(college);
			college.addNewLectureToCourse(*createLecture(college, *course), *course);
		case 'r':
			return 'r'; // return to main menu and resume
		case 'q':
			return 'q';	// return to main menu and exit
		default:
			break;
		}
	} while (choice != 'q');
	return 'q';
}


void printArray(void** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "\t" << (i + 1) << ". " << arr[i];
	}
}

Person* getPersonInfo()
{
	char name[PERSON_NAME_LEN];
	char id[PERSON_ID_LEN];
	int day, month, year;

	cout << "Please enter name: ";
	cin >> name;
	cout << "Please enter id: ";
	cin >> id;
	cout << "Please enter date (d m y): ";
	cin >> day >> month >> year;

	Date date(day, month, year);

	return new Person(name, date, id);
}


void printStudents(College& c)
{
	int numOfStudents = 0;
	Student** students = c.getStudents(&numOfStudents);
	printArray((void**)students, numOfStudents);
}

Student* getStudentById(College& c)
{
	char id[PERSON_ID_LEN];
	cout << "Please enter student ID: ";
	cin >> id;

	return c.getStudentById(id);
}

Student* getStudentInfo()
{
	Person* p = getPersonInfo();
	Student::eDepartmenType depEnum;
	int dep;

	cout << "Please choose department:" << endl << "Software / Medical / Electricity: ";
	cin >> dep;
	depEnum = (Student::eDepartmenType)dep;

	return new Student(p->getName(), p->getBirthDate(), p->getId(), depEnum);
}

Lecture* chooseLectureOfCourse(College& c)
{
	Course* course = getCourseByName(c);
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
	cin >> lIndex;
	if (lIndex == 0 || lIndex >= numOfLectures)
	{
		cout << "Invalid choice" << endl;
		return nullptr;
	}
	lIndex--; // real index
	return lectures[lIndex];
}

Lecture* createLecture(College& college, Course& course)
{
	Lecture* lecture;
	Lecture::eType lectureType = (Lecture::eType)1;
	Lecture::eWeekDay lectureDay;
	int lecDay, lectureStartHour, lectureDuration, lectureRoomNumber;

	cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
	cin >> lecDay;
	lectureDay = (Lecture::eWeekDay)lecDay;
	cout << "Please enter lecture start hour: ";
	cin >> lectureStartHour;
	cout << "Please enter lecture duration: ";
	cin >> lectureDuration;
	cout << "Please enter lecture classroom number: ";
	cin >> lectureRoomNumber;
	ClassRoom* lectureRoom = college.getClassRoomByNumber(lectureRoomNumber);

	Professor* lectureProf = getProfessorById(college);
	if (!lectureProf)
	{
			cout << "Can not find proffesor";
		return nullptr;
	}



	Lecture::eType pracType = (Lecture::eType)0;
	Lecture::eWeekDay practiceDay;
	int pracDay, pracStartHour, pracDuration, pracRoomNumber;

	cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
	cin >> pracDay;
	practiceDay = (Lecture::eWeekDay)pracDay;
	cout << "Please enter lecture start hour: ";
	cin >> pracStartHour;
	cout << "Please enter lecture duration: ";
	cin >> pracDuration;
	cout << "Please enter lecture classroom number: ";
	cin >> pracRoomNumber;
	ClassRoom* pracRoom = college.getClassRoomByNumber(lectureRoomNumber);

	Practitioner* practiceProf = getPractitionerById(college);
	if (!practiceProf)
	{
		cout << "Can not find proffesor";
		return nullptr;
	}

	Lecture* lecturePract = new Lecture(practiceDay, pracStartHour, pracDuration, pracType,
		course, *pracRoom, *practiceProf, nullptr);

	lecture = new Lecture(lectureDay, lectureStartHour, lectureDuration, lectureType, course, *lectureRoom,
		*lectureProf, lecturePract);

	return lecture;
}

void printProfessors(College& c)
{
	int numOfProfessors = 0;
	Professor** professors = c.getProfessors(&numOfProfessors);
	printArray((void**)professors, numOfProfessors);
}

Professor* getProfessorById(College& c)
{
	char id[PERSON_ID_LEN];
	cout << "Please enter professor ID: ";
	cin >> id;

	return c.getProfessorById(id);
}

Practitioner* getPractitionerById(College& c)
{
	char id[PERSON_ID_LEN];
	cout << "Please enter practitioner ID: ";
	cin >> id;

	return c.getPractitionerById(id);
}

Professor* getProfessorInfo()
{
	Person* p = getPersonInfo();
	double salary;

	cout << "Please enter salary: ";
	cin >> salary;

	return  new Professor(p->getName(), p->getBirthDate(), p->getId(), salary);
}

void printCourses(College& c)
{
	int numOfCourses = 0;
	Course** courses = c.getCourses(&numOfCourses);
	printArray((void**)courses, numOfCourses);
}

Course& getCourseInfo(College& college)
{
	char name[COURSE_NAME_SIZE];
	float points;

	cout << "Please enter course name: ";
	cin >> name;
	cout << "Please enter number of points: ";
	cin >> points;
	cout << "Please choose a professor to be the coordinator of the course";
	Professor* coordinator = getProfessorById(college);

	Course *c = new Course(name, coordinator, points);
	return *c;
}

Course* getCourseByName(College& c)
{
	char name[COURSE_NAME_SIZE];
	cout << "Please enter course name: ";
	cin >> name;

	return c.getCourseByName(name);
}

void setGrades(College& c, Professor& prof)
{
	int lecId, arrSize = 0;
	const Lecture * const * arr = prof.getLectures(&arrSize);
	printArray((void**)arr, arrSize);

	cout << "Please enter lecture ID: ";
	cin >> lecId;

	const Lecture* lecture = nullptr;
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i]->getId() == lecId)
		{
			lecture = arr[i];
			break;
		}
	}
	
	if (!lecture)
		return;

	int studentListSize = 0;
	const Student** studentList = lecture->getStudentList(&studentListSize);

	int grade = 0;
	for (int i = 0; i < studentListSize; i++)
	{
		cout << studentList[i] << ", Please enter grade: ";
		cin >> grade;
		studentList[i]->updateGrade(*lecture, grade);
	}
}