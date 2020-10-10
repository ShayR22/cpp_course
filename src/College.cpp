#include "College.h"


College::College(int maxAllStudents, int maxAllProfessors, int maxAllCourses, int maxAllClassRooms) noexcept(false) :
    numOfStudents(0), maxStudents(NULL),
    numOfProfessors(0), maxProfessors(NULL),
    numOfPractitioners(0), maxPractitioners(NULL),
    numOfCourses(0), maxCourses(NULL),
    numOfClassRooms(0), maxClassRooms(NULL)
{
    if (maxAllStudents < 0)
        throw "Invalid max students: ", maxAllStudents;
    if (maxAllProfessors < 0)
        throw "Invalid max professors: ", maxAllProfessors;
    if (maxAllCourses < 0)
        throw "Invalid max courses: ", maxAllCourses;
    if (maxAllClassRooms < 0)
        throw "Invalid max class-rooms: ", maxAllClassRooms;

    this->maxStudents = maxAllStudents;
    this->maxProfessors = maxAllProfessors;
    this->maxPractitioners = maxAllProfessors;
    this->maxCourses = maxAllCourses;
    this->maxClassRooms = maxAllClassRooms;
    
    students = new Student * [maxStudents];
    professors = new Professor * [maxProfessors];
    practitioners = new Practitioner * [maxPractitioners];
    courses = new Course * [maxCourses];
    classRooms = new ClassRoom * [maxClassRooms];
}

int College::getStudentIndex(const char* id) const
{
    for (int i = 0; i < numOfStudents; i++)
        if (*(students[i]) == id)
            return i;
    return -1;
}

int College::getPractitionerIndex(const char* id) const
{
    for (int i = 0; i < numOfPractitioners; i++)
        if (*(practitioners[i]) == id)
            return i;
    return -1;
}

int College::getProfessorIndex(const char* id) const
{
    for (int i = 0; i < numOfProfessors; i++)
        if (*(professors[i]) == id)
            return i;
    return -1;
}

int College::getCourseIndex(const char* name) const
{
    for (int i = 0; i < numOfCourses; i++)
        if (*(courses[i]) == name)
            return i;
    return -1;
}

int College::getClassRoomIndex(int roomNumber) const
{
    for (int i = 0; i < numOfClassRooms; i++)
        if (*(classRooms[i]) == roomNumber)
            return i;
    return -1;
}

bool College::addClassRoom(const ClassRoom& newClassroom)
{
    if (getClassRoomIndex(newClassroom.getRoomNumber()) >= 0)
        return false;

    if (numOfClassRooms >= maxClassRooms)
        return false;

    *classRooms[numOfClassRooms++] = newClassroom;
    return true;
}

bool College::removeClassRoom(int index)
{
    if (index < 0)
        return false;

    removeClassRoomFromAllLectures(*classRooms[index]);

    delete classRooms[index];
    int numEleToMove = numOfClassRooms - index - 1;
    if (numEleToMove > 0)
        memmove(&classRooms[index], &classRooms[index + 1], sizeof(ClassRoom*) * numEleToMove);
    classRooms[--numOfClassRooms] = nullptr;

    return true;
}

bool College::removeClassRoom(const ClassRoom& classRoomToRemove)
{
    int index = getClassRoomIndex(classRoomToRemove.getRoomNumber());
    return removeClassRoom(index);
}

const ClassRoom* College::getClassRoomByNumber(int roomNumber) const
{
    return nullptr;
}

const ClassRoom* const* College::getClassRooms(int* numOfClassRooms) const
{
    return nullptr;
}

void College::printClassRooms(std::ostream& os) const
{

}

bool College::addCourse(const Course& newCourse)
{
    if (getCourseIndex(newCourse.getCourseName()) >= 0)
        return false;
    if (numOfProfessors >= maxProfessors)
        return false;

    *courses[numOfCourses++] = newCourse;
    return true;
}

bool College::removeCourse(int index)
{
    if (index < 0 || index > numOfCourses - 1)
        return false;

    delete courses[index];
    int numEleToMove = numOfCourses - index - 1;
    if (numEleToMove > 0)
        memmove(&courses[index], &courses[index + 1], sizeof(Course*) * numEleToMove);
    courses[--numOfCourses] = nullptr;

    return true;
}

bool College::removeCourse(const Course& courseToRemove)
{
    int index = getCourseIndex(courseToRemove.getCourseName());
    return removeCourse(index);
}

bool College::setCourseName(const char* name, const char* newName)
{
    return false;
}

bool College::setCoursePoints(const char* name, float points)
{
    return false;
}

bool College::addNewLectureToCourse(const char* courseName, const Lecture& newLecture)
{
	return false;
}

bool College::removeLectureFromCourse(const char* courseName, int id)
{
	return false;
}

bool College::addConditionCourseToCourse(const char* name, const Course& c)
{
	return false;
}

bool College::removeConditionCourseFromCourse(const char* name, const char* remove)
{
	return false;
}

/* NOTE: return also the current number of courses */
const Course* const* College::getCourses(int* numOfCourses) const
{
    *numOfCourses = this->numOfCourses;
    return courses;
}

const Course* College::getCourseByName(const char* name) const
{
    int courseIndex = getCourseIndex(name);
    if (courseIndex < 0)
        return nullptr;
    return this->courses[courseIndex];
}

void College::printCourses(std::ostream& os) const
{

}

// Lecture
bool College::addLectureToCourse(const Lecture& lecture, const char* courseName)
{
	return false;
}

bool College::removeLectureFromCourse(const Lecture& lecture, const char* courseName)
{
	return false;
}

bool College::setLectureWeekDay(const char* courseName, const Lecture& lecture, Lecture::eWeekDay day)
{
	return false;
}

bool College::setLecturStartHour(const char* courseName, const Lecture& lecture, int hour)
{
	return false;
}

bool College::setLectureDuration(const char* courseName, const Lecture& lecture, int durationHours)
{
	return false;
}

bool College::setMaxStudentList(const char* courseName, const Lecture& lecture, int newMaxStudents)
{
	return false;
}

bool College::setLectureType(const char* courseName, const Lecture& lecture, Lecture::eType type)
{
	return false;
}

bool College::setLectureClassroom(const char* courseName, const Lecture& lecture, int roomNumber)
{
	return false;
}

bool College::setLectureLecturer(const char* courseName, const Lecture& lecture, const char* professorID)
{
	return false;
}

bool College::setLecturePractitioner(const char* courseName, const Lecture& lecture, const char* practitionerID)
{
	return false;
}

bool College::addStudentToLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID)
{
	return false;
}

bool College::removeStudentFromLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID)
{
	return false;
}

// Student
bool College::addStudent(const Student& newStudent)  // TODO: there was const on newStudent
{
    // if student exist
    if (getStudentIndex(newStudent.getName()) >= 0)
        return false;

    if (numOfStudents >= maxStudents)
        return false;

    students[numOfStudents++] = new Student(newStudent);
    return true;
}

bool College::removeStudent(const char* studentID)
{
	return false;
}

bool College::setStudentDepartment(const char* studentID, Student::eDepartmenType newDepartmentType)
{
	return false;
}

bool College::updateStudentGrade(const char* studentID, const Lecture& lecture, int newGrade)
{
	return false;
}

bool College::addLectureToStudent(const char* studentID, const Lecture& lecture)
{
	return false;
}

bool College::removeStudentFromCourse(const char* studentID, const char* courseName)
{
	return false;
}

const Student* const* College::getStudents(int* numOfStudents)const
{
    *numOfStudents = this->numOfStudents;
    return students;
}

const Student* College::getStudentById(const char* id) const
{
    for (int i = 0; i < numOfStudents; i++)
        if (*(students[i]) == id)
            return students[i];

    return nullptr;
}

void College::printStudents(std::ostream& os) const
{

}

bool College::addProfessor(const Professor& newProfessor)
{
    if (getProfessorIndex(newProfessor.getName()) >= 0)
        return false;


    if (numOfProfessors >= maxProfessors)
        return false;

    *professors[numOfProfessors++] = newProfessor;
    return true;
}

bool College::removeProfessor(const char* id)
{
	return false;
}

bool College::setProfesssorSalary(const char* id, double newSalary)
{
	return false;
}

bool College::addLectureToProfessor(const char* id, const Lecture* newLecture)
{
	return false;
}

bool College::removeLectureFromProfessor(const char* id, const Lecture* lectureToRemove)
{
	return false;
}

/* NOTE: return also the current number of professors */
const Professor* const* College::getProfessors(int* numOfProfessors) const
{
    *numOfProfessors = this->numOfProfessors;
    return professors;
}

const Professor* College::getProfessorById(const char* id) const
{
    for (int i = 0; i < numOfProfessors; i++)
        if (*(professors[i]) == id)
            return professors[i];
    return nullptr;
}

void College::printProfessors(std::ostream& os) const
{
    
}

// Practitioner
bool College::addPractitioner(const Practitioner& newPractitioner)
{
    if (getPractitionerIndex(newPractitioner.getName()) >= 0)
        return false;

    if (numOfPractitioners >= maxPractitioners)
        return false;

    practitioners[numOfPractitioners++] = new Practitioner(newPractitioner);
    return true;
}

bool College::removePractitioner(const char* id)
{
	return false;
}

bool College::setPractitionerSalary(const char* id, double newSalary)
{
	return false;
}

bool College::addPracticeToPractitioner(const char* id, const Lecture* newLecture)
{
	return false;
}

bool College::removePracticeFromPractitioner(const char* id, const Lecture* lectureToRemove)
{
	return false;
}

bool College::setPractitionerDepartment(const char* id, Student::eDepartmenType newDepartmentType)
{
	return false;
}

bool College::updatePractitionerGrade(const char* id, const Lecture& lecture, int newGrade)
{
	return false;
}

/* TODO give better name from the student fucntions of practitioner */
bool College::addLectureToPractitioner(const char* id, const Lecture& lecture)
{
	return false;
}

bool College::removePractitionerFromCourse(const char* id, const char* courseName)
{
	return false;
}

const Practitioner* const* College::getPractitioners(int* numOfPractitioners) const
{
    *numOfPractitioners = this->numOfPractitioners;
    return practitioners;
}

const Practitioner* College::getPractitionerById(const char* id) const
{
    for (int i = 0; i < numOfPractitioners; i++)
        if (*practitioners[i] == id)
            return practitioners[i];

    return nullptr;
}

void College::printPractitioners(std::ostream& os) const
{

}

void College::removeStudentFromAllLectures(Student* removeStudent)
{
    int numOfLectures = -1;
    Lecture** lectures;
    for (int i = 0; i < numOfCourses; i++)
    {
        lectures = courses[i]->getLectures(&numOfLectures);
        for (int j = 0; j < numOfLectures; j++)
            lectures[j]->removeStudent(*removeStudent);
    }
}

bool College::removeStudent(int index)
{
    if (index < 0 || index > numOfStudents - 1)
        return false;

    removeStudentFromAllLectures(students[index]);
    delete students[index];
    
    int numEleToMove = numOfStudents - index - 1;
    if (numEleToMove > 0)
        memmove(&students[index], &students[index + 1], sizeof(Student*) * numEleToMove);
    students[--numOfStudents] = nullptr;
    return true;
}

bool College::removePractitioner(int index)
{
    if (index < 0 || index > numOfPractitioners - 1)
        return false;

    // remove the practitioner from all lectures and courses...
    removeProfessorFromAllCourses(*practitioners[index]);
    removeStudentFromAllLectures(practitioners[index]);
    
    delete practitioners[index];

    int numEleToMove = numOfStudents - index - 1;
    if (numEleToMove > 0)
        memmove(&practitioners[index], &practitioners[index + 1], sizeof(Practitioner*) * numEleToMove);
    practitioners[--numOfPractitioners] = nullptr;
    
    return true;
}

void College::removeProfessorFromAllCourses(Professor & removeProfessor)
{
    for (int i = 0; i < numOfCourses; i++)
        if (*courses[i]->getCoordinator() == removeProfessor)
            courses[i]->setCoordinator(nullptr);
}

bool College::removeProfessor(int index)
{
    if (index < 0)
        return false;

    removeProfessorFromAllCourses(*professors[index]);
    delete professors[index];
    int numEleToMove = numOfStudents - index - 1;
    if (numEleToMove > 0)
        memmove(&professors[index], &professors[index + 1], sizeof(Professor*) * numEleToMove);
    professors[--numOfProfessors] = nullptr;
    
    return true;
}

void College::removeClassRoomFromAllLectures(const ClassRoom& c)
{
    int numOfLectures = -1;
    for (int i = 0; i < numOfCourses; i++)
    {
        Lecture** lectures = courses[i]->getLectures(&numOfLectures);
        for (int j = 0; j < numOfLectures; j++)
            if (lectures[j]->getClassRoom() == c)
                lectures[j]->setClassRoom(nullptr);
    }
}

const College & College::operator+=(Course & c)
{
    addCourse(c);
    return *this;
}		

const College& College::operator+=(const Student& s)
{
    addStudent(s);
    return *this;
}	

const College& College::operator+=(const Professor& p)
{
    addProfessor(p);
    return *this;
}	

const College& College::operator+=(const Practitioner& p)
{
    addPractitioner(p);
    return *this;
}

const College& College::operator+=(const ClassRoom& cr)
{
    addClassRoom(cr);
    return *this;
}

const College& College::operator-=(const ClassRoom& cr)
{
    removeClassRoom(cr);
    return *this;
}

std::ostream & operator<<(std::ostream & os, const College & c)
{
    int numOfStudents = c.numOfStudents;
    const Student* const* s = c.students;
    
        	/*int numOfProfessors;
        +	const Professor*const* prof = c.getProfessors(&numOfProfessors);
        +
        +	int numOfPractitioners;
        +	const Practitioner* const* prac = c.getPractitioners(&numOfPractitioners);*/
        
     os << "College - Details: \n\n" << "students: \n";
     // for (int i = 0; i < numOfStudents; i++)
     // 	os << "Student " << i + 1 << ", Details: " << *s[i];
     return os;
}

College::~College()
{
    // remove when start from backward is more efficient: 0 pointers' moves, except to O(n^2)
    for (int i = numOfPractitioners - 1; i >= 0; i--)
        removePractitioner(i);
    delete practitioners;
    
    for (int i = numOfStudents - 1; i >= 0; i--)
        removeStudent(i);
    delete students;
    
    for (int i = numOfProfessors - 1; i >= 0; i--)
        removeProfessor(i);
    delete professors;
    
    for (int i = numOfClassRooms - 1; i >= 0; i--)
        removeClassRoom(i);
    delete classRooms;
    
    for (int i = numOfCourses - 1; i >= 0; i--)
        removeCourse(i);
    delete courses;

}
