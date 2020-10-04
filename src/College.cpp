#include "College.h"

College::College(int maxAllStudents, int maxAllProfessors, int maxAllCourses, int maxAllClassRooms)
{

}

Student** College::getStudents(int* numOfStudents)const
{
	return nullptr;
} // return also the current number of students


bool College::addStudent(const Student& newStudent)
{
	return false;
}

bool College::removeStudent(const Student& studentToRemove)
{
	return false;
}

Student* College::getStudentById(const char* id)
{
	return nullptr;
}

Practitioner** College::getPractitioners(int* numOfPractitioners)const
{
	return nullptr;
} // return also the current number of professors

bool College::addPractitioner(const Professor& newPractitioner)
{
	return false;
}

bool College::removePractitioner(const Professor& practitionerToRemove)
{
	return false;
}

Practitioner* College::getPractitionerById(const char* id)
{
	return nullptr;
}

Professor** College::getProfessors(int* numOfProfessors)const
{
	return nullptr;
} // return also the current number of professors

bool College::addProfessor(const Professor& newProfessor)
{
	return false;
}

bool College::removeProfessor(const Professor& professorToRemove)
{
	return false;
}

Professor* College::getProfessorById(const char* id)
{
	return nullptr;
}

Course** College::getCourses(int* numOfCourses) const
{
	return nullptr;
} // return also the current number of courses

bool College::addCourse(const Course& newCourse)
{
	return false;
}

bool College::removeCourse(const Course& courseToRemove)
{
	return false;
}

Course* College::getCourseByName(const char* name)
{
	return nullptr;
}

bool College::addNewLectureToCourse(const Lecture& newLecture, const Course& course)
{
	return false;
}

// return also the current number of ClassRooms
const ClassRoom** College::getClassRooms(int* numOfClassRooms)
{
	return nullptr;
}

bool College::addClassRoom(const ClassRoom& newClassroom)
{
	return false;
}

bool College::removeClassRoom(const ClassRoom& classRoomToRemove)
{
	return false;
}

ClassRoom* College::getClassRoomByNumber(int number)
{
	return nullptr;
}

const College& College::operator+=(const Course& c)
{
	return *this;
}		//	use college.addCourse

const College& College::operator+=(const Student& s)
{
	return *this;
}	//	use college.addStudent

const College& College::operator+=(const Professor& p)
{
	return *this;
}	//	use college.addProfessor

const College& College::operator+=(const Practitioner& p)
{
	return *this;
}	//	use college.addPractitioner

const College& College::operator+=(const ClassRoom& cr)
{
	return *this;
}		//	use college.addClassRoom

const College& College::operator-=(const ClassRoom& cr)
{
	return *this;
}		//	use college.removeClassRoom

College::~College()
{

}
