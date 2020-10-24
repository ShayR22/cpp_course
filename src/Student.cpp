#include <iostream>
#include "Student.h"
#include "Professor.h"

using namespace std;

Student::Student(const char* name, const Date& birthDate, const char* id,
	eDepartmenType department, int maxOfCourses) noexcept(false):
	Person(name, birthDate, id), department(department), maxOfCourses(maxOfCourses), numOfCourses(0),
	courses(nullptr)
{
	if (maxOfCourses <= 0)
		throw - 1;
	courses = new CourseInformation*[maxOfCourses];
}

Student::Student(const Student& other) noexcept : Person(other), 
	department(other.department), maxOfCourses(other.maxOfCourses), numOfCourses(other.numOfCourses)
{
	courses = new CourseInformation*[maxOfCourses];

	for (int i = 0; i < maxOfCourses; i++)
	{
		if (i < numOfCourses)
		{
			CourseInformation* cur_course = other.courses[i];
			courses[i] = new CourseInformation(cur_course->getLecture(), cur_course->getGrade());
		}
		else
		{
			courses[i] = nullptr;
		}
	}
}

void Student::destroyCourses()
{
	for (int i = 0; i < numOfCourses; i++)
		delete courses[i];
	delete courses;
}

Student& Student::operator=(const Student& other)
{
	Person::operator=(other);
	destroyCourses();

	this->maxOfCourses = other.maxOfCourses;
	this->numOfCourses = other.numOfCourses;
	courses = new CourseInformation * [this->maxOfCourses];

	for (int i = 0; i < maxOfCourses; i++)
	{
		if (i < numOfCourses)
		{
			CourseInformation* cur_course = other.courses[i];
			courses[i] = new CourseInformation(cur_course->getLecture(), cur_course->getGrade());
		}
		else
		{
			courses[i] = nullptr;
		}
	}
	return *this;
}

Student& Student::operator=(Student&& other) noexcept
{
	Person::operator=(other);

	this->maxOfCourses = other.maxOfCourses;
	this->numOfCourses = other.numOfCourses;
	this->courses = other.courses;
	other.courses = nullptr;
	other.maxOfCourses = 0;
	other.numOfCourses = 0;
	return *this;
}

Student::~Student()
{
	destroyCourses();
}

const char* Student::getDepartmentString() const
{
	if (department == eDepartmenType::SOFTWARE)
		return "Software";
	else if (department == eDepartmenType::MEDICAL)
		return "Medical";
	else
		return "Electricity";
}

Student::Student(Student&& otherS) noexcept : Person(otherS), department(otherS.department),
	maxOfCourses(otherS.maxOfCourses), numOfCourses(otherS.numOfCourses)
{
	courses = otherS.courses;
	otherS.courses = nullptr;
}

void Student::setDepartment(eDepartmenType newDepartmentType)
{
	department = newDepartmentType;
}

const CourseInformation * const * Student::getCourseInformation(int* numOfCourses) const
{
	*numOfCourses = this->numOfCourses;
	return courses;
}

bool Student::isValidGrade(int grade) const
{
	return grade >= 1 && grade <= 100;
}


bool Student::updateGrade(const Lecture& lecture, int newGrade) const
{
	if (!isValidGrade(newGrade))
		return false;

	for (int i = 0; i < numOfCourses; i++)
	{
		if (lecture.getId() == courses[i]->getLecture()->getId())
		{
			courses[i]->setGrade(newGrade);
			return true;
		}
	}
	return false;
}

bool Student::addLecture(const Lecture* newLecture)
{
	if (!newLecture)
	{
		cout << "Lecturer cant be null" << endl;
		return false;
	}
	if (numOfCourses >= maxOfCourses)
	{
		cout << "Courses are full, cant take any more courses" << endl;
		return false;
	}

	courses[numOfCourses++] = new CourseInformation(newLecture);
	return true;
}

bool Student::deleteFromCourse(Course& c)
{
	int numLectures;
	Lecture** lectures_ptrs = c.getLectures(&numLectures);

	for (int i = 0; i < numLectures; i++)
	{
		Lecture* cur_lec = lectures_ptrs[i];
		if (cur_lec->removeStudent(*this))
			return true;
	}
	return false;
}

bool Student::passedCourse(const Course* c)
{
	for (int i = 0; i < numOfCourses; i++)
	{
		const Course& cur_c = courses[i]->getLecture()->getCourse();
		if (*c == cur_c)
			return true;
	}
	return false;
}

bool Student::qualify(const Course& c)
{
	int numCourses;
	const Course* const* conditionCourses = c.getConditionsCourses(&numCourses);
	for (int i = 0; i < numCourses; i++)
		if (!passedCourse(&c))
			return false;

	return true;
}

void Student::printGrades(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "haven't finished any courses" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		os << *courses[i];
	}
}

void Student::printProfessores(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "doesn't have any courses, thus, no proffesors" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		const Professor& p = courses[i]->getLecture()->getLecturer();
		/*if (p == NULL)
			os << "Lecturer not exist to lecture: " << courses[i]->getLecture()->getId() << endl;
		else*/
		p.print(os);
	}
}

void Student::printProfessoresNames(ostream& os) const
{
	if (numOfCourses == 0)
	{
		os << "doesn't have any courses, thus, no proffesors" << endl;
		return;
	}

	for (int i = 0; i < numOfCourses; i++)
	{
		const Professor& p = courses[i]->getLecture()->getLecturer();
		os << p.getName() << " (id:" << p.getId() << ")";
		if (i < numOfCourses - 1)
			os << ", ";
		else
			os << endl;
	}
}

void Student::printAddition(ostream& os) const
{
	os << "Department: " << getDepartmentString() << endl;
	printGrades(os);
	printProfessoresNames(os);
}

void Student::print(ostream& os) const
{
	Person::print(os);
	Student::printAddition(os);
}

const Student& Student::operator+=(const Lecture& l)
{
	if (!addLecture(&l))
		cout << "failed to add lecture" << endl;
	return *this;
}
