#include "College.h"

using namespace std;

College::College(int maxAllStudents, int maxAllProfessors, int maxAllCourses, int maxAllClassRooms) noexcept(false) :
    maxStudents(maxAllStudents), maxProfessors(maxAllProfessors), maxPractitioners(maxAllProfessors),
    maxCourses(maxAllCourses), maxClassRooms(maxAllCourses)
{
    if (maxAllStudents < 0)
        throw "Invalid max students: ", maxAllStudents;
    if (maxAllProfessors < 0)
        throw "Invalid max professors: ", maxAllProfessors;
    if (maxAllCourses < 0)
        throw "Invalid max courses: ", maxAllCourses;
    if (maxAllClassRooms < 0)
        throw "Invalid max class-rooms: ", maxAllClassRooms;
}

bool College::addClassRoom(const ClassRoom& newClassroom)
{
    if (classRooms.find(newClassroom.getRoomNumber()) != classRooms.end())
        return false;

    if ((int)classRooms.size() >= maxClassRooms)
        return false;

    classRooms[newClassroom.getRoomNumber()] = new ClassRoom(newClassroom);
    return true;
}

bool College::removeClassRoom(const ClassRoom& classRoomToRemove)
{
    if (!classRooms.erase(classRoomToRemove.getRoomNumber()))
    {
        cout << "class room was not found" << endl;
        return false;
    }
    return true;
}

const ClassRoom* College::getClassRoomByNumber(int roomNumber) const
{
    map<int, ClassRoom*>::const_iterator pos = classRooms.find(roomNumber);

    if (pos == classRooms.end())
    {
        cout << "classroom was not found " << endl;
        return nullptr;
    }

    return pos->second;
}

const map<int, const ClassRoom*> College::getClassRooms() const
{
    map<int, const ClassRoom*> constClassRooms;

    for (auto& e : classRooms)
        constClassRooms[e.first] = e.second;

    return constClassRooms;
}

void College::printClassRooms(ostream& os) const
{
    if (classRooms.size() <= 0) {
        os << "College has no classrooms" << endl;
        return;
    }

    os << "\nAll Class-Rooms:";
    for (auto& e : classRooms)
        os << *(e.second);
}

// course
bool College::addCourse(const Course& newCourse)
{
    return addT(newCourse, newCourse.getCourseName(), &courses, maxCourses);
}

bool College::removeCourse(const Course& courseToRemove)
{
    return removeT(courseToRemove.getCourseName(), &courses);
}

bool College::setCourseName(const string& name, const string& newName)
{
    if (courses.find(name) == courses.end())
    {
        cout << "cant find course" << endl;
        return false;
    }
    return courses[name]->setCourseName(newName);
}

bool College::setCoursePoints(const string& name, float points)
{
    if (courses.find(name) == courses.end())
        return false;
    return courses[name]->setPoints(points);
}


bool College::addNewLectureToCourse(const string& courseName, const Lecture& newLecture)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->addLecture(newLecture);
}

bool College::removeLectureFromCourse(const string& courseName, int id)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->removeLecture(id);
}

bool College::addConditionCourseToCourse(const string& name, const Course& c)
{
    if (courses.find(name) == courses.end())
        return false;
    return courses[name]->addConditionCourse(c);
}

bool College::removeConditionCourseFromCourse(const string& name, const string& remove)
{
    if (courses.find(name) == courses.end())
        return false;
    return courses[name]->removeConditionCourse(remove);
}

/* NOTE: return also the current number of courses */
const map<string, const Course*> College::getCourses() const
{
    map<string, const Course*> constCourses;

    for (auto& e : courses)
        constCourses[e.first] = e.second;

    return constCourses;
}

const Course* College::getCourseByName(const string& name) const
{
    map<string, Course*>::const_iterator pos = courses.find(name);

    if (pos == courses.end())
        return nullptr;
    return pos->second;
}

void College::printCourses(std::ostream& os) const
{
    if (courses.size() <= 0)
    {
        os << "College has no courses" << endl;
        return;
    }

    os << "\nAll Courses:";
    for (auto& e : courses)
        os << *(e.second);
}


// Lecture
bool College::setLectureWeekDay(const string& courseName, const Lecture& lecture, Lecture::eWeekDay day)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->setLectureWeekDay(lecture, day);
}

bool College::setLecturStartHour(const string& courseName, const Lecture& lecture, int hour)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->setLecturStartHour(lecture, hour);
}

bool College::setLectureDuration(const string& courseName, const Lecture& lecture, int durationHours)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->setLectureDuration(lecture, durationHours);
}

bool College::setMaxStudentList(const string& courseName, const Lecture& lecture, int newMaxStudents)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->setLectureMaxStudents(lecture, newMaxStudents);
}

bool College::setLectureType(const string& courseName, const Lecture& lecture, Lecture::eType type)
{
    if (courses.find(courseName) == courses.end())
        return false;
    return courses[courseName]->setLectureType(lecture, type);
}

bool College::setLectureClassroom(const string& courseName, const Lecture& lecture, int roomNumber)
{
    if (courses.find(courseName) == courses.end())
        return false;

    // check classroom exist
    if (classRooms.find(roomNumber) == classRooms.end())
        return false;

    return courses[courseName]->setLectureClassroom(lecture, classRooms[roomNumber]);
}

bool College::setLectureLecturer(const string& courseName, const Lecture& lecture, const string& professorID)
{
    if (courses.find(courseName) == courses.end())
        return false;

    // check professor exist
    if (professors.find(professorID) == professors.end())
        return false;

    return courses[courseName]->setLectureLecturer(lecture, professors[professorID]);
}

bool College::setLecturePractitioner(const string& courseName, const Lecture& lecture, const string& practitionerID)
{
    if (courses.find(courseName) == courses.end())
        return false;

    if (practitioners.find(practitionerID) == practitioners.end())
        return false;

    return courses[courseName]->setLectureLecturer(lecture, practitioners[practitionerID]);
}

bool College::addStudentToLectureWaitingList(const string& courseName, const Lecture& lecture, const string& studentID)
{
    if (courses.find(courseName) == courses.end())
        return false;

    if (students.find(studentID) == students.end())
        return false;
    return courses[courseName]->addStudentToWaitingListCourse(lecture, *(students[studentID]));
}

bool College::removeStudentFromLectureWaitingList(const string& courseName, const Lecture& lecture, const string& studentID)
{
    if (courses.find(courseName) == courses.end())
        return false;

    if (students.find(studentID) == students.end())
        return false;
    return courses[courseName]->removeStudentToWaitingListCourse(lecture, *(students[studentID]));
}

// Student
bool College::addStudent(const Student& newStudent)
{
    return addT(newStudent, newStudent.getId(), &students, maxStudents);
}

bool College::removeStudent(const string& studentID)
{
    return removeT(studentID, &students);
}

bool College::setStudentDepartment(const string& studentID, Student::eDepartmenType newDepartmentType)
{
    if (students.find(studentID) == students.end())
    {
        cout << "Student not in College" << endl;
        return false;
    }

    students[studentID]->setDepartment(newDepartmentType);
    return true;
}

bool College::updateStudentGrade(const string& studentID, const Lecture& lecture, int newGrade)
{
    if (students.find(studentID) == students.end())
    {
        cout << "Student not in College" << endl;
        return false;
    }

    return students[studentID]->updateGrade(lecture, newGrade);
}

bool College::addLectureToStudent(const string& studentID, const Lecture& lecture)
{
    if (students.find(studentID) == students.end())
    {
        cout << "Student not in College" << endl;
        return false;
    }

    const string& cname = lecture.getCourse().getCourseName();

    if (courses.find(cname) == courses.end())
    {
        cout << "Lectures course not found in college" << endl;
        return false;
    }

    Course* course = courses[cname];
    Student* student = students[studentID];

    return course->addStudentToCourse(lecture, *student) == Course::eAddingStudentStatus::SUCCESS;
}

bool College::removeStudentFromCourse(const string& studentID, const string& courseName)
{
    if (courses.find(courseName) == courses.end())
    {
        cout << "Course Not Found" << endl;
        return false;
    }
    Course& courseToRemove = *(courses[courseName]);

    if (students.find(studentID) == students.end())
    {
        cout << "Student not in College" << endl;
        return false;
    }

    students[studentID]->deleteFromCourse(courseToRemove);
    return true;
}

const map<string, const Student*> College::getStudents() const
{
    map<string, const Student*> constStudents;
 
    for (auto& e : students)
        constStudents[e.first] = e.second;
 
    return constStudents;
}

const Student* College::getStudentById(const string& id) const
{
    for (auto& e : students)
        if (*(e.second) == id)
            return e.second;
   
    return nullptr;
}

void College::printStudents(std::ostream& os) const
{
    if (students.size() <= 0)
        os << "College has no students" << endl;

    for (auto& e : students)
        os << *(e.second);

}

void College::printProfessorsOfStudent(std::ostream& os, const string& id)
{
    if (students.find(id) == students.end())
    {
        os << "Failed to find student with id " << id << endl;
        return;
    }

    students[id]->printProfessores(os);
}


bool College::addProfessor(const Professor& newProfessor)
{
    return addT(newProfessor, newProfessor.getId(), &professors, maxProfessors);
}

bool College::removeProfessor(const string& id)
{
    return removeT(id, &professors);
}

bool College::setProfesssorSalary(const string& id, double newSalary)
{
    if (professors.find(id) == professors.end())
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[id]->setSalary(newSalary);
}

bool College::addLectureToProfessor(const string& id, const Lecture* newLecture)
{
    if (professors.find(id) == professors.end())
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[id]->addLectureTeaching(newLecture);
}

bool College::removeLectureFromProfessor(const string& id, const Lecture* lectureToRemove)
{
    if (professors.find(id) == professors.end())
    {
        cout << "Professor wasn't found" << endl;
        return false;
    }

    return professors[id]->removeLecture(lectureToRemove);
}

const map<string, const Professor*> College::getProfessors() const
{
    map<string, const Professor*> constProfessors;
    
    for (auto& e : professors)
        constProfessors[e.first] = e.second;

    return constProfessors;
}

const Professor* College::getProfessorById(const string& id) const
{
    for (auto& e : professors)
        if (*(e.second) == id)
            return e.second;

    return nullptr;
}

void College::printProfessors(std::ostream& os) const
{
    if (professors.size() <= 0)
        os << "College has no professors" << endl;

    for (auto& e : professors)
        os << *(e.second);
}

void College::printProfessorsOfStudent(ostream& os, const string& id) const
{
    map<string, Student*>::const_iterator pos = students.find(id);
    if (pos == students.end())
    {
        os << "Student wasn't found" << endl;
        return;
    }

    pos->second->printProfessores(os);
}

int College::getNumOfProfessors() const
{
    return professors.size();
}

// Practitioner
bool College::addPractitioner(const Practitioner& newPractitioner)
{
    return addT(newPractitioner, newPractitioner.getId(), &practitioners, maxPractitioners);
}

bool College::removePractitioner(const string& id)
{
    return removeT(id, &practitioners);
}

bool College::setPractitionerSalary(const string& id, double newSalary)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[id]->setSalary(newSalary);
}

bool College::addPracticeToPractitioner(const string& id, const Lecture* newLecture)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[id]->addLectureTeaching(newLecture);
}

bool College::removePracticeFromPractitioner(const string& id, const Lecture* lectureToRemove)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[id]->removeLecture(lectureToRemove);
}

bool College::setPractitionerDepartment(const string& id, Student::eDepartmenType newDepartmentType)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    practitioners[id]->setDepartment(newDepartmentType);
    return true;
}

bool College::setLecturesPractice(const string& courseName, int lecID, int pracID)
{
    if (courses.find(courseName) == courses.end())
    {
        cout << "course does not exist" << endl;
        return false;
    }
    return courses[courseName]->setLecturePractice(lecID, pracID);
}

bool College::updatePractitionerGrade(const string& id, const Lecture& lecture, int newGrade)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[id]->updateGrade(lecture, newGrade);
}

bool College::addLectureToPractitioner(const string& id, const Lecture& lecture)
{
    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner wasn't found" << endl;
        return false;
    }

    return practitioners[id]->addLecture(&lecture);
}

bool College::removePractitionerFromCourse(const string& id, const string& courseName)
{
    if (courses.find(courseName) == courses.end())
    {
        cout << "Course Not Found" << endl;
        return false;
    }
    Course& courseToRemove = *(courses[courseName]);

    if (practitioners.find(id) == practitioners.end())
    {
        cout << "Practitioner not in College" << endl;
        return false;
    }

    return practitioners[id]->deleteFromCourse(courseToRemove);
}

const map<string, const Practitioner*> College::getPractitioners() const
{
    map<string, const Practitioner*> constPractitioners;

    for (auto& e : practitioners)
        constPractitioners[e.first] = e.second;

    return constPractitioners;
}

const Practitioner* College::getPractitionerById(const string& id) const
{
    for (auto& e: practitioners)
        if (*(e.second) == id)
            return e.second;

    return nullptr;
}

void College::printPractitioners(std::ostream& os) const
{
    if (practitioners.size() <= 0)
        os << "College has no practitioners" << endl;

    for (auto &e : practitioners)
        os << *(e.second);
}

void College::removeStudentFromAllLectures(Student* removeStudent)
{
    for (auto &e : courses)
        e.second->removeStudentFromCourse(*removeStudent);
}

void College::removeProfessorFromAllCourses(Professor& removeProfessor)
{

    for (auto& e : courses)
        if (*e.second->getCoordinator() == removeProfessor)
            e.second->setCoordinator(nullptr);
}

void College::removeClassRoomFromAllLectures(const ClassRoom& c)
{
    for (auto& ce : courses)
    {
        map<int, Lecture*> lectures = ce.second->getLectures();
        for (auto& e : lectures)
            if (e.second->getClassRoom() == c)
                e.second->setClassRoom(nullptr);
    }
}

const Lecture* College::getLecture(const string& courseName, int lectureId)
{
    if (courses.find(courseName) == courses.end())
        return nullptr;
    return courses[courseName]->getLectureById(lectureId);
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

}
