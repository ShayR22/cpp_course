#include "College.h"


using namespace std;


College::College(int maxAllStudents, int maxAllProfessors, int maxAllCourses, int maxAllClassRooms) noexcept(false) :
    numOfStudents(0), maxStudents(maxAllStudents),
    numOfProfessors(0), maxProfessors(maxAllProfessors),
    numOfPractitioners(0), maxPractitioners(maxAllProfessors),
    numOfCourses(0), maxCourses(maxAllCourses),
    numOfClassRooms(0), maxClassRooms(maxAllClassRooms)
{
    if (maxAllStudents < 0)
        throw "Invalid max students: ", maxAllStudents;
    if (maxAllProfessors < 0)
        throw "Invalid max professors: ", maxAllProfessors;
    if (maxAllCourses < 0)
        throw "Invalid max courses: ", maxAllCourses;
    if (maxAllClassRooms < 0)
        throw "Invalid max class-rooms: ", maxAllClassRooms;
    
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

    classRooms[numOfClassRooms++] = new ClassRoom(newClassroom);
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
    int index = getClassRoomIndex(roomNumber);
    if (index < 0)
        return nullptr;
    return classRooms[index];
}

const ClassRoom* const* College::getClassRooms(int* numOfClassRooms) const
{
    *numOfClassRooms = this->numOfClassRooms;
    return classRooms;
}

void College::printClassRooms(std::ostream& os) const
{
    os << "\nAll Class-Rooms:";
    for (int i = 0; i < numOfClassRooms; i++)
        os << "\n" << *(classRooms[i]);
}

// course
bool College::addCourse(const Course& newCourse)
{
    if (getCourseIndex(newCourse.getCourseName()) >= 0)
        return false;
    if (numOfCourses >= maxCourses)
        return false;

    courses[numOfCourses++] = new Course(newCourse);
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
    int index = getCourseIndex(name);
    if (index < 0)
        return false;
    return courses[index]->setCourseName(name);
}

bool College::setCoursePoints(const char* name, float points)
{
    int index = getCourseIndex(name);
    if (index < 0)
        return false;
    return courses[index]->setPoints(points);
}


bool College::addNewLectureToCourse(const char* courseName, const Lecture& newLecture)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->addLecture(newLecture);
}

bool College::removeLectureFromCourse(const char* courseName, int id)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->removeLecture(id);
}

bool College::addConditionCourseToCourse(const char* name, const Course& c)
{
    int index = getCourseIndex(name);
    if (index < 0)
        return false;
    return courses[index]->addConditionCourse(c);
}

bool College::removeConditionCourseFromCourse(const char* name, const char* remove)
{
    int index = getCourseIndex(name);
    if (index < 0)
        return false;
    return courses[index]->removeConditionCourse(remove);
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
    if (numOfCourses == 0)
    {
        os << "No Courses in college!" << endl;
        return;
    }
        
    os << "All Courses:" << endl;
    for (int i = 0; i < numOfCourses; i++)
        os << *(courses[i]) << endl;
}


// Lecture
bool College::setLectureWeekDay(const char* courseName, const Lecture& lecture, Lecture::eWeekDay day)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->setLectureWeekDay(lecture, day);
}

bool College::setLecturStartHour(const char* courseName, const Lecture& lecture, int hour)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->setLecturStartHour(lecture, hour);
}

bool College::setLectureDuration(const char* courseName, const Lecture& lecture, int durationHours)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->setLectureDuration(lecture, durationHours);
}

bool College::setMaxStudentList(const char* courseName, const Lecture& lecture, int newMaxStudents)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->setLectureMaxStudents(lecture, newMaxStudents);
}

bool College::setLectureType(const char* courseName, const Lecture& lecture, Lecture::eType type)
{
    int index = getCourseIndex(courseName);
    if (index < 0)
        return false;
    return courses[index]->setLectureType(lecture, type);
}

bool College::setLectureClassroom(const char* courseName, const Lecture& lecture, int roomNumber)
{
    int lectureIndex = getCourseIndex(courseName);
    if (lectureIndex < 0)
        return false;

    // check classroom exist
    int roomIndex = getClassRoomIndex(roomNumber);
    if (roomIndex < 0)
        return false;
    return courses[lectureIndex]->setLectureClassroom(lecture, classRooms[roomIndex]);
}

bool College::setLectureLecturer(const char* courseName, const Lecture& lecture, const char* professorID)
{
    int lectureIndex = getCourseIndex(courseName);
    if (lectureIndex < 0)
        return false;

    // check professor exist
    int professorIndex = getProfessorIndex(professorID);
    if (professorIndex < 0)
        return false;

    return courses[lectureIndex]->setLectureLecturer(lecture, professors[professorIndex]);
}

bool College::setLecturePractitioner(const char* courseName, const Lecture& lecture, const char* practitionerID)
{
    int lectureIndex = getCourseIndex(courseName);
    if (lectureIndex < 0)
        return false;

    int practitionerIndex = getPractitionerIndex(practitionerID);
    if (practitionerIndex < 0)
        return false;

    return courses[lectureIndex]->setLectureLecturer(lecture, practitioners[practitionerIndex]);
}

bool College::addStudentToLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID)
{
    int lectureIndex = getCourseIndex(courseName);
    if (lectureIndex < 0)
        return false;

    int studentIndex = getStudentIndex(studentID);
    if (studentIndex < 0)
        return false;
    return courses[lectureIndex]->addStudentToWaitingListCourse(lecture, *(students[studentIndex]));
}

bool College::removeStudentFromLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID)
{
    int lectureIndex = getCourseIndex(courseName);
    if (lectureIndex < 0)
        return false;

    int studentIndex = getStudentIndex(studentID);
    if (studentIndex < 0)
        return false;
    return courses[lectureIndex]->removeStudentToWaitingListCourse(lecture, *(students[studentIndex]));
}

// Student
bool College::addStudent(const Student& newStudent)
{
    if (getStudentIndex(newStudent.getId()) >= 0)
    {
        cout << "Student with same id already exist, ID: " << newStudent.getId() << endl;
        return false;
    }

    if (numOfStudents >= maxStudents)
    {
        cout << "College is full of students." << endl;
        cout << "Num of students: " << numOfStudents << endl;
        return false;
    }

    students[numOfStudents++] = new Student(newStudent);
    return true;
}

bool College::removeStudent(const char* studentID)
{
    int index = getStudentIndex(studentID);
    if (index < 0)
    {
        cout << "Student not in College" << endl;
        return false;
    }

    removeStudent(index);

    for (int i = 0; i < numOfCourses; i++)
        removeStudentFromCourse(studentID, courses[i]->getCourseName());
    return true;
}

bool College::setStudentDepartment(const char* studentID, Student::eDepartmenType newDepartmentType)
{
    int index = getStudentIndex(studentID);
    if (index < 0)
    {
        cout << "Student not in College" << endl;
        return false;
    }

    students[index]->setDepartment(newDepartmentType);
    return true;
}

bool College::updateStudentGrade(const char* studentID, const Lecture& lecture, int newGrade)
{
    int index = getStudentIndex(studentID);
    if (index < 0)
    {
        cout << "Student not in College" << endl;
        return false;
    }

    return students[index]->updateGrade(lecture, newGrade);
}

bool College::addLectureToStudent(const char* studentID, const Lecture& lecture)
{
    int studentIndex = getStudentIndex(studentID);
    if (studentIndex < 0)
    {
        cout << "Student not in College" << endl;
        return false;
    }

    int courseIndex = getCourseIndex(lecture.getCourse().getCourseName());
    if (courseIndex < 0)
    {
        cout << "Lecture' course not in College" << endl;
        return false;
    }
    
    Course::eAddingStudentStatus status = courses[courseIndex]->addStudentToCourse(lecture, *students[studentIndex]);
    return status == Course::eAddingStudentStatus::SUCCESS;
}

bool College::removeStudentFromCourse(const char* studentID, const char* courseName)
{
    int courseIndex = getCourseIndex(courseName);
    if (courseIndex)
    {
        cout << "Course Not Found" << endl;
        return false;
    }
    Course& courseToRemove = *(courses[courseIndex]);

    int studentIndex = getStudentIndex(studentID);
    if (studentIndex < 0)
    {
        cout << "Student not in College" << endl;
        return false;
    }

    return students[studentIndex]->deleteFromCourse(courseToRemove);
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
    if (numOfStudents <= 0)
        os << "College has no students" << endl;

    for (int i = 0; i < numOfStudents; i++)
        os << *(students[i]) << endl;
}

void College::printProfessorsOfStudent(std::ostream& os, const char* id)
{
    int index = getStudentIndex(id);
    if (index < 0)
    {
        os << "Failed to find student with id " << id << endl;
        return;
    }

    students[index]->printProfessores(os);
}


bool College::addProfessor(const Professor& newProfessor)
{
    if (getProfessorIndex(newProfessor.getId()) >= 0)
    {
        cout << "Professor with same id already exist, ID: " << newProfessor.getId() << endl;
        return false;
    }

    if (numOfProfessors >= maxProfessors)
    {
        cout << "College is full of professors." << endl;
        cout << "Num of professors: " << numOfProfessors << endl;
        return false;
    }

    professors[numOfProfessors++] = new Professor(newProfessor);
    return true;
}

bool College::removeProfessor(const char* id)
{
    int index = getProfessorIndex(id);
    if (index < 0)
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return removeProfessor(index);
}

bool College::setProfesssorSalary(const char* id, double newSalary)
{
    int index = getProfessorIndex(id);
    if (index < 0)
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[index]->setSalary(newSalary);
}

bool College::addLectureToProfessor(const char* id, const Lecture* newLecture)
{
    if (newLecture->getLectureType() != Lecture::eType::LECTURE)
    {
        cout << "Lecture must be lecture type" << endl;
        return false;
    }

    int index = getProfessorIndex(id);
    if (index < 0)
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[index]->addLectureTeaching(newLecture);
}

bool College::removeLectureFromProfessor(const char* id, const Lecture* lectureToRemove)
{
    int index = getProfessorIndex(id);
    if (index < 0)
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[index]->removeLecture(lectureToRemove);
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
    if (numOfProfessors <= 0)
        os << "College has no professors" << endl;

    for (int i = 0; i < numOfProfessors; i++)
        os << *(professors[i]) << endl;
}

void College::printProfessorsOfStudent(std::ostream& os, const char* id) const
{
    int index = getStudentIndex(id);
    if (index < 0) {
        os << "Student wasn't found" << endl;
        return;
    }

    students[index]->printProfessores(os);
}

// Practitioner
bool College::addPractitioner(const Practitioner& newPractitioner)
{
    if (getPractitionerIndex(newPractitioner.getId()) >= 0)
    {
        cout << "Practitioner with same id already exist, ID: " << newPractitioner.getId() << endl;
        return false;
    }
        
    if (numOfPractitioners >= maxPractitioners)
    {
        cout << "College is full of practitioners." << endl;
        cout << "Num of practitioners: " << numOfPractitioners << endl;
        return false;
    }

    practitioners[numOfPractitioners++] = new Practitioner(newPractitioner);
    return true;
}

bool College::removePractitioner(const char* id)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return removePractitioner(index);
}

bool College::setPractitionerSalary(const char* id, double newSalary)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[index]->setSalary(newSalary);
}

bool College::addPracticeToPractitioner(const char* id, const Lecture* newLecture)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[index]->addLectureTeaching(newLecture);
}

bool College::removePracticeFromPractitioner(const char* id, const Lecture* lectureToRemove)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[index]->removeLecture(lectureToRemove);
}

bool College::setPractitionerDepartment(const char* id, Student::eDepartmenType newDepartmentType)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    practitioners[index]->setDepartment(newDepartmentType);
    return true;
}

bool College::setLecturesPractice(const char* courseName, int lecID, int pracID)
{
    int courseIndex = getCourseIndex(courseName);
    if (courseIndex < 0)
    {
        cout << "course does not exist" << endl;
        return false;
    }
    return courses[courseIndex]->setLecturePractice(lecID, pracID);
}


bool College::updatePractitionerGrade(const char* id, const Lecture& lecture, int newGrade)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[index]->updateGrade(lecture, newGrade);
}

bool College::addLectureToPractitioner(const char* id, const Lecture& lecture)
{
    int index = getPractitionerIndex(id);
    if (index < 0)
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[index]->addLecture(&lecture);
}

bool College::removePractitionerFromCourse(const char* id, const char* courseName)
{
    int courseIndex = getCourseIndex(courseName);
    if (courseIndex)
    {
        cout << "Course Not Found" << endl;
        return false;
    }
    Course& courseToRemove = *(courses[courseIndex]);

    int practitionerIndex = getPractitionerIndex(id);
    if (practitionerIndex < 0)
    {
        cout << "Practitioner not in College" << endl;
        return false;
    }

    return practitioners[practitionerIndex]->deleteFromCourse(courseToRemove);
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
    if (numOfPractitioners <= 0)
        os << "College has no practitioners" << endl;

    for (int i = 0; i < numOfPractitioners; i++)
        os << *(practitioners[i]) << endl;
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

    delete practitioners[index];

    int numEleToMove = numOfPractitioners - index - 1;
    if (numEleToMove > 0)
        memmove(&practitioners[index], &practitioners[index + 1], sizeof(Practitioner*) * numEleToMove);
    practitioners[--numOfPractitioners] = nullptr;
    return true;
}

void College::removeProfessorFromAllCourses(Professor& removeProfessor)
{
    for (int i = 0; i < numOfCourses; i++)
    {
        bool isEqual = *courses[i]->getCoordinator() == removeProfessor;
        if (isEqual)
            courses[i]->setCoordinator(nullptr);
    }
}

bool College::removeProfessor(int index)
{
    if (index < 0)
        return false;

    removeProfessorFromAllCourses(*professors[index]);
    delete professors[index];
    int numEleToMove = numOfProfessors - index - 1;
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

const Lecture* College::getLecture(const char* courseName, int lectureId)
{
    const Course* cur_course = nullptr;
    for (int i = 0; i < numOfCourses; i++)
    {
        if (*courses[i] == courseName) {
            cur_course = courses[i];
            break;
        }
    }
    if (cur_course == nullptr)
        return nullptr;

    return cur_course->getLectureById(lectureId);
}

const College& College::operator+=(const Course& c)
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

std::ostream& operator<<(std::ostream& os, const College& c)
{
    c.printClassRooms(os);
    c.printCourses(os);
    c.printProfessors(os);
    c.printPractitioners(os);
    c.printStudents(os);
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
