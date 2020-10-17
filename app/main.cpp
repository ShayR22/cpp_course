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
eSystemStatus choosePractitionerMenu(College& college);
eSystemStatus chooseCoursesMenu(College& college);

// Student menu
Student Dummy_getStudentInfoFromUser();
Student getStudentInfoFromUser(ostream& errorOs);
Lecture* chooseLectureOfCourseFromUser(College& c);

// Professor menu
Professor Dummy_getProfessorInfoFromUser();
Professor getProfessorInfoFromUser(ostream& errorOs);
const char* getProfessorIdFromUser();
void setGradesByUser(College& c, const char* profName, ostream& os);

// Practitioner
Practitioner Dummy_getPractitionerInfoFromUser();
Practitioner getPractitionerInfoFromUser(ostream& errorOs);

// Course menu
Course getCourseInfoFromUser(College& college, ostream& os);
void getCourseNameFromUser(char *courseName);
Lecture getLectureInfoFromUser(College& college, const Course& course, const Lecture* practice, Lecture::eType lectureType, ostream& errorOs);

Person getPersonInfoFromUser(ostream& errorOs);
const char* getStudentIdFromUser();
const char* getPractitionerIdFromUser();

void readCollege()
{
	// TODO
	// ofstream outFile("../college.txt", ios::app);
	ifstream outFile("../college.txt");
}

static void initlaize_with_data(College* c)
{
	c->addStudent(Student("aviv", Date(2000, 12, 12), "1", Student::eDepartmenType::SOFTWARE));
	c->addStudent(Student("shay", Date(2000, 11, 10), "2", Student::eDepartmenType::SOFTWARE));
	c->addStudent(Student("yoni", Date(2000, 8, 9), "3", Student::eDepartmenType::SOFTWARE));
	c->addStudent(Student("tom", Date(1880, 3, 3), "100", Student::eDepartmenType::ELECTRICITY));

	Professor *keren = new Practitioner("keren", Date(2000, 11, 10), "10", Student::eDepartmenType::SOFTWARE, 30000);

	c->addProfessor(*keren);
	c->addPractitioner(*(dynamic_cast<Practitioner*>(keren)));

	delete keren;

	c->addProfessor(Practitioner("vladislav", Date(1999, 11, 10), "11", Student::eDepartmenType::ELECTRICITY, 15000));

	c->addClassRoom(ClassRoom(100, 40));
	c->addClassRoom(ClassRoom(101, 40));
	c->addClassRoom(ClassRoom(102, 40));
	c->addClassRoom(ClassRoom(103, 40));

	c->addCourse(Course("C++", c->getProfessorById("10"), 3));
	c->addCourse(Course("Physics", c->getProfessorById("11"), 5));

	// define C++ course
	Lecture cppPractice(Lecture::eWeekDay::FRIDAY, 11, 1, Lecture::eType::PRACTICE, *c->getCourseByName("C++"),
		*c->getClassRoomByNumber(101), *c->getProfessorById("10"), nullptr);
	c->addNewLectureToCourse("C++", cppPractice);

	const Lecture* l = c->getLecture("C++", cppPractice.getId());
	Lecture cpp(Lecture::eWeekDay::FRIDAY, 8, 3, Lecture::eType::LECTURE, *c->getCourseByName("C++"),
		*c->getClassRoomByNumber(101), *c->getProfessorById("10"), l);
	c->addNewLectureToCourse("C++", cpp);

	// add amazing keren to C++ lecture
	c->addLectureToProfessor("10", c->getLecture("C++", cpp.getId()));

	// define Pysics course
	/*Lecture phsicsPractice(Lecture::eWeekDay::SUNDAY, 20, 1, Lecture::eType::PRACTICE, *c->getCourseByName("Physics"),
		*c->getClassRoomByNumber(102), *c->getProfessorById("11"), nullptr);
	c->addNewLectureToCourse("Physics", cppPractice);*/

	Lecture electrocuteHuman(Lecture::eWeekDay::SUNDAY, 18, 3, Lecture::eType::LECTURE, *c->getCourseByName("Physics"),
		*c->getClassRoomByNumber(103), *c->getProfessorById("11"), nullptr);
	c->addNewLectureToCourse("Physics", electrocuteHuman);

	// add king vladislav to lecture:
	int lecId = electrocuteHuman.getId();
	c->addLectureToProfessor("11", c->getLecture("Physics", lecId));

	// add students to C++ lecture
	int cppId = cpp.getId();
	const Lecture* userChosenLecture = c->getLecture("C++", cppId);

	c->addLectureToStudent("1", *userChosenLecture);
	c->updateStudentGrade("1", *userChosenLecture, 95);

	c->addLectureToStudent("2", *userChosenLecture);
	c->updateStudentGrade("2", *userChosenLecture, 100);

	c->addLectureToStudent("3", *userChosenLecture);
	c->updateStudentGrade("3", *userChosenLecture, 99);

	// add students to Physics lecture
	int pysicsId = electrocuteHuman.getId();
	userChosenLecture = c->getLecture("Physics", pysicsId);

	c->addLectureToStudent("2", *userChosenLecture);
	c->updateStudentGrade("2", *userChosenLecture, 96);

	c->addLectureToStudent("3", *userChosenLecture);

	//c->addLectureToStudent("3", *c->getLecture("Physics", pysicsId));
	//c->updateStudentGrade("3", *c->getLecture("Physics", pysicsId), 90);
}

int main(int argc, char** argv)
{
	College* college = new College();
	initlaize_with_data(college);

	//	TODO: load classes from file		////////////////////////////////////////
	//	TODO: load practitioners from file	////////////////////////////////////////

	eSystemStatus choice;
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
	cout << "3. Practitioner menu" << endl;
	cout << "4. Courses menu" << endl;
	cout << "'q' to exit" << endl;
	cin >> choice;

	switch (choice)
	{
	case '1':
		return chooseStudentsMenu(college);
	case '2':
		return chooseProfessorsMenu(college);
	case '3':
		return choosePractitionerMenu(college);
	case '4':
		return chooseCoursesMenu(college);
	case 'q':
		return eSystemStatus::QUIT;
	default:
		cout << "Please try again" << endl;
		cleanBuffer();
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
			break;

		case '2':
			if (college.addStudent(getStudentInfoFromUser(cout)))
			//if (college.addStudent(getStudentInfoFromUser(cout)))
				cout << "Succeed Add student!" << endl;
			else
				cout << "Failed Add student!" << endl;
			break;

		case '3':
			studentId = getStudentIdFromUser();
			if (college.removeStudent(studentId))
				cout << "Student removed" << endl;
			else
				cout << "Student did not removed" << endl;
			break;

		case '4':
			studentId = getStudentIdFromUser();
			student = college.getStudentById(studentId);
			if (student)
				student->printGrades(cout);
			else
				cout << "No student with ID: " << studentId << " not found!" << endl;

			break;
		case '5':
			studentId = getStudentIdFromUser();
			if (!college.getStudentById(studentId))
			{
				cout << "No student with ID: " << studentId << " not found!" << endl;
				break;
			}

			l = chooseLectureOfCourseFromUser(college);
			if (!l)
				break;

			if ( college.addLectureToStudent(studentId, *l) )
				cout << "Succeeded adding student to course" << endl;
			else
				cout << "Failed adding student to course" << endl;
			break;
		case '6':
			studentId = getStudentIdFromUser();
			student = college.getStudentById(studentId);
			if (student != nullptr)
				college.printProfessorsOfStudent(cout, studentId);
			else
				cout << "Failed to find student with ID: " << studentId;
			break;

		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume

		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit

		default:
			cout << "Invalid input: " << choice << endl;
		}
	} while (true);
}


int i_student = 0;
Student Dummy_getStudentInfoFromUser()
{
	char buffer[2] = { 0 };
	buffer[0] = i_student++ + '0';

	Student s = Student("aviv", Date(2000, 12, 12), buffer, Student::eDepartmenType::SOFTWARE);
	return s;
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
		if (dep < 0 || dep > 2)
		{
			cout << "Invalid department number: " << dep;
			continue;
		}

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
		cin >> year >> month >> day;

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
	char courseName[32];
	getCourseNameFromUser(courseName);
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
		cout << (i + 1) << ". " << *lectures[i] << endl;
	}
	int lIndex;
	cout << "Lecture number (NOT ID!): ";
	cleanBuffer();
	cin >> lIndex;
	if (lIndex == 0 || lIndex > numOfLectures)
	{
		cout << "Invalid lecture number: " << lIndex << endl;
		return nullptr;
	}
	return lectures[--lIndex];
}

void getCourseNameFromUser(char * name)
{
	cout << "Please enter course name: ";
	cleanBuffer();
	cin >> name;
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
			break;
		case '2':
			if (college.addProfessor(getProfessorInfoFromUser(cout)))
			//if (college.addProfessor(getProfessorInfoFromUser(cout)))
				cout << "Sucess Adding Professor!" << endl;
			else
				cout << "Failed Adding Professor!" << endl;
			break;
		case '3':
			cout << "Removing Professor\n";
			professorId = getProfessorIdFromUser();
			if (college.removeProfessor(professorId))
				cout << "Professor removed";
			else
				cout << "Professor did not removed\n";
			break;
		case '4':
			professorId = getProfessorIdFromUser();
			p = college.getProfessorById(professorId);
			if (p != nullptr)
				p->printLectures(cout);
			break;
		case '5':
			professorId = getProfessorIdFromUser();
			setGradesByUser(college, professorId, cout);
			break;
		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume
		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit
		default:
			cout << "Invalid input: " << choice << endl;
		}
	} while (true);
}

int i_professor = 0;
Professor Dummy_getProfessorInfoFromUser()
{
	char buffer[2] = { 0 };
	buffer[0] = i_professor++ + '0';
	return Professor("keren", Date(1970, 1, 1), buffer, 2000);
}

Professor getProfessorInfoFromUser(ostream& errorOs)
{
	Person p = getPersonInfoFromUser(errorOs);
	double salary;
	
	do
	{
		cout << "\nPlease enter salary: ";
		cleanBuffer();
		cin >> salary;
		try
		{
			return Professor(p.getName(), p.getBirthDate(), p.getId(), salary);
		}
		catch (const char* msg)
		{
			cout << msg << endl;
		}
	} while (true);
}

const char* getProfessorIdFromUser()
{
	static char profId[PERSON_ID_LEN];  // TODO: fix it
	cout << "\nPlease enter Professor ID: ";
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
	
	const Professor* p = college.getProfessorById(profName);
	if (p == nullptr)
	{
		cout << "failed to find " << profName << endl;
		return;
	}

	p->printLectures(os);

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

	if (!(lecture->getLecturer() == *p))
	{
		cout << "missmatch between lecture and professor" << endl;
		return;
	}

	int studentListSize = 0;
	const Student*const* studentList = lecture->getStudentList(&studentListSize);

	int grade = 0;
	const char* studentId;
	bool sucess;
	for (int i = 0; i < studentListSize; i++)
	{
		studentId = studentList[i]->getId();
		do
		{
			cout << "Student ID " << studentId << ", Please enter valid grade: ";
			cleanBuffer();
			cin >> grade;
			
			sucess = college.updateStudentGrade(studentId, *lecture, grade);
			if (!sucess)
				cout << "Your grade is invalid: " << grade << endl;
		} while (!sucess);
	}
}


eSystemStatus choosePractitionerMenu(College& college)
{
	char choice = '0';
	const char* practitionerId;

	do
	{
		cout << "\n1. Print all Practitioner" << endl;
		cout << "2. Add practitioner to college" << endl;
		cout << "3. Remove practitioner from college" << endl;
		cout << "'r' to return, 'q' to exit" << endl;
		cout << "Your choice: ";
		cleanBuffer();
		cin >> choice;

		switch (choice)
		{
		case '1':
			college.printPractitioners(cout);
			break;

		case '2':
			if (college.addPractitioner(getPractitionerInfoFromUser(cout)))
				cout << "Succeed Add practitioner!" << endl;
			else
				cout << "Failed Add practitioner!" << endl;
			break;

		case '3':
			practitionerId = getPractitionerIdFromUser();
			if (college.removePractitioner(practitionerId))
				cout << "Practitioner removed sucessfully" << endl;
			else
				cout << "Practitioner did not removed" << endl;
			break;

		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume

		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit

		default:
			cout << "Invalid input: " << choice << endl;
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

int i_practitioner = 0;
Practitioner Dummy_getPractitionerInfoFromUser()
{
	char buffer[2] = { 0 };
	buffer[0] = i_practitioner++ + '0';
	Practitioner p = Practitioner("aviv", Date(2000, 12, 12), buffer, Student::eDepartmenType::SOFTWARE, 2000);
	return p;
}

Practitioner getPractitionerInfoFromUser(ostream& errorOs)
{
	double salary;
	int depNum;
	Student::eDepartmenType dep;
	
	do
	{
		Person p = getPersonInfoFromUser(errorOs);

		cout << "\nPlease enter salary: ";
		cleanBuffer();
		cin >> salary;

		cout << "Please choose department:" << endl << "0: Software / 1: Medical / 2: Electricity: ";
		cleanBuffer();
		cin >> depNum;
		dep = Student::eDepartmenType(depNum);

		try
		{
			return Practitioner(p.getName(), p.getBirthDate(), p.getId(), dep, salary);
		}
		catch (int) {}  // TODO: change the catch
	} while (true);
}


eSystemStatus chooseCoursesMenu(College& college)
{

	const Course* course = nullptr;
	char courseName[32];
	char choice = '0';
	do
	{
		cout << "\n1. Print all courses" << endl;
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
			cout << "---------------------------" << endl;
			college.printCourses(cout);
			break;
		case '2':
			try
			{
				/*Course c = getCourseInfoFromUser(college, cout);
				bool sucess = college.addCourse(c);
				if (sucess)*/
				if(college.addCourse(getCourseInfoFromUser(college, cout)))
					cout << "Add course sucessfully!" << endl;
				else
					cout << "Failed add course!";
			}
			catch (const char* msg)
			{
				cout << msg << endl;
			}
			break;
		case '3':
			// TODO: maybe to create a new college func: removeCourse(courseName)
			getCourseNameFromUser(courseName);
			course = college.getCourseByName(courseName);
			if (course != nullptr && college.removeCourse(*course))
				cout << "Remove course successfully!";
			else
				"Failed remove course!";
			break;
		case '4':
			getCourseNameFromUser(courseName);
			course = college.getCourseByName(courseName);
			if (course != nullptr)
			{
				cout << "Enter PRACTICE info:" << endl;
				Lecture practice = getLectureInfoFromUser(college, *course, nullptr, Lecture::eType::PRACTICE, cout);
				cout << "Enter LECTURE info:" << endl;
				Lecture lecture = getLectureInfoFromUser(college, *course, &practice, Lecture::eType::LECTURE, cout);
				
				bool goodHours = true;
				if (practice.getWeekDay() == lecture.getWeekDay()) {
					int pHour = practice.getHour();
					int pDuration = practice.getDuration();
					int lHour = lecture.getHour();
					int lDuration = lecture.getDuration();
					if ((pHour > lHour && lHour + lDuration > pHour) ||
						(lHour > pHour && pHour + pDuration > lHour)) 
					{
						cout << "Invalid hours" << endl;
						goodHours = false;
					}
				}
				if (goodHours) {
					college.addNewLectureToCourse(courseName, lecture);
					college.addNewLectureToCourse(courseName, practice);
					college.setLecturesPractice(courseName, lecture.getId(), practice.getId());
				}

			}
			break;
		case 'r':
			return eSystemStatus::RESUME; // return to main menu and resume
		case 'q':
			return eSystemStatus::QUIT;	// return to main menu and exit
		default:
			break;
		}
	} while (true);
}

//int i_course = 0;
//Course Dummy_getCourseInfoFromUser()
//{
//	char buffer[6] = "algo";
//	buffer[5] = i_course++ + '0';
//
//	return Course(buffer, --, 2.5);
//}

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
		if (!coordinator)
		{
			cout << "coordinator with ID : " << profId << " not exist in college!" << endl;
			if (college.getNumOfProfessors() == 0)
				throw "Because there are no professors in college, we return to main menu!";
			else
			{
				cout << "Possible professors list:" << endl;
				college.printProfessors(cout);
			}
		}

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


Lecture getLectureInfoFromUser(College& college, const Course& course, const Lecture* practice, Lecture::eType lectureType, ostream& errorOs)
{
	int pracDay, pracStartHour, pracDuration, pracRoomNumber;
	const char* id;
	const ClassRoom* pracRoom;
	const Professor* practiceProf;

	do{
		cout << "Starting procedure for Lecture Detailes" << endl;
		cout << "Please enter lecture classroom number: ";
		cin >> pracRoomNumber;
		pracRoom = college.getClassRoomByNumber(pracRoomNumber);
		if (!pracRoom)
		{
			cout << "There is no classroom in college with number: " << pracRoomNumber;
			continue;
		}

		if (lectureType == Lecture::eType::LECTURE)
		{
			id = getProfessorIdFromUser();
			practiceProf = college.getPractitionerById(id);
		}
		else
		{
			id = getPractitionerIdFromUser();
			practiceProf = college.getPractitionerById(id);
		}
		
		if (!practiceProf)
		{
			cout << "Can not find proffesor with ID: " << id << endl;
			continue;
		}

		cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
		cin >> pracDay;
		cout << "Please enter lecture start hour: ";
		cin >> pracStartHour;
		cout << "Please enter lecture duration: ";
		cin >> pracDuration;

		try
		{
			return Lecture((Lecture::eWeekDay)pracDay, pracStartHour, pracDuration, lectureType,
				course, *pracRoom, *practiceProf, practice);
		}
		catch (const char* msg)
		{
			errorOs << msg << endl;
		}
	} while (true);
}







Lecture __getLectureInfoFromUser__(College& college, const Course& course, ostream& errorOs)
{
	Lecture::eType lectureType = Lecture::eType::LECTURE;
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
		cout << "LECTURE info:" << endl;
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
		if (!lectureRoom)
		{
			cout << "There is no classroom in college with number: " << lectureRoomNumber;
			continue;
		}

		profId = getProfessorIdFromUser();
		lectureProf = college.getProfessorById(profId);
		if (!lectureProf)
		{
			cout << "Can not find proffesor";
			continue;
		}

	} while (true);

	do {
		Lecture::eType pracType = Lecture::eType::PRACTICE;
		Lecture::eWeekDay practiceDay;

		cout << "LECTURE info:" << endl;
		cout << "Please enter lecture classroom number: ";
		cin >> pracRoomNumber;
		pracRoom = college.getClassRoomByNumber(pracRoomNumber);
		if (!pracRoom)
		{
			cout << "There is no classroom in college with number: " << pracRoomNumber;
			continue;
		}
		cout << "Please choose lecture day (1 = sunday, ... , 6 = friday): ";
		cin >> pracDay;
		practiceDay = (Lecture::eWeekDay)pracDay;
		cout << "Please enter lecture start hour: ";
		cin >> pracStartHour;
		cout << "Please enter lecture duration: ";
		cin >> pracDuration;

		practitionerId = getPractitionerIdFromUser();
		practiceProf = college.getPractitionerById(practitionerId);
		if (!practiceProf)
		{
			cout << "Can not find proffesor with ID: " << practitionerId << endl;
			continue;
		}

		try
		{
			return Lecture(practiceDay, pracStartHour, pracDuration, pracType,
				course, *pracRoom, *practiceProf, nullptr);
		}
		catch (const char* msg)
		{
			errorOs << msg << endl;
		}
	} while (true);
}




