#ifndef __H_COLLEGE__
#define __H_COLLEGE__

#include "Course.h"
#include "Person.h"
#include "Practitioner.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "ClassRoom.h"
#include <map>

class College
{
private:

    template<typename T>
    bool addT(const T& element, const std::string& id, std::map<std::string, T*>* map, int maxTAllowed)
    {
        if (map->find(id) != map->end())
        {
            std::cout << typeid(T).name() << " with same id already exist, ID: " << id << std::endl;
            return false;
        }
        if ((int)map->size() >= maxTAllowed)
        {
            std::cout << "College is full of " << typeid(T).name() << "." << std::endl;
            return false;
        }

        (*map)[id] = new T(element);
        return true;
    }

    template<typename T>
    bool removeT(const std::string& elementID, std::map<std::string, T*>* map)
    {
        if (!map->erase(elementID))
        {
            std::cout << typeid(T).name() << " not in College" << std::endl;
            return false;
        }
        return true;
    }

    std::map<std::string, Student *> students;
    int maxStudents;

    std::map<std::string, Professor*> professors;
    int maxProfessors;
    
    std::map<std::string, Practitioner*> practitioners;
    int maxPractitioners;
    
    std::map<std::string, Course*>courses;
    int maxCourses;
    
    std::map<int, ClassRoom*> classRooms;
    int maxClassRooms;

public:
    College(int maxAllStudents = 100, int maxAllProfessors = 100, int maxAllCourses = 100,
            int maxAllClassRooms = 100) noexcept(false);

    // ClassRoom
    bool addClassRoom(const ClassRoom& newClassroom);
    bool removeClassRoom(const ClassRoom& classRoomToRemove);
    const ClassRoom* getClassRoomByNumber(int roomNumber) const;
    const std::map<int, const ClassRoom*> getClassRooms() const;
    void printClassRooms(std::ostream& os) const;

    // Course
    bool addCourse(const Course& newCourse);
    bool removeCourse(const Course& courseToRemove);
    bool setCourseName(const std::string& name, const std::string& newName);
    bool setCoursePoints(const std::string& name, float points);
    bool addNewLectureToCourse(const std::string& courseName, const Lecture& newLecture);
    bool removeLectureFromCourse(const std::string& courseName, int id);
    bool addConditionCourseToCourse(const std::string& name, const Course& c);
    bool removeConditionCourseFromCourse(const std::string&name, const std::string&remove);
    const std::map<std::string, const Course*> getCourses() const;
    const Course* getCourseByName(const std::string& name) const;
    void printCourses(std::ostream& os) const;

    // Lecture
    bool setLectureWeekDay(const std::string& courseName, const Lecture& lecture, Lecture::eWeekDay day);
    bool setLecturStartHour(const std::string& courseName, const Lecture& lecture, int hour);
    bool setLectureDuration(const std::string& courseName, const Lecture& lecture, int durationHours);
    bool setMaxStudentList(const std::string& courseName, const Lecture& lecture, int newMaxStudents);
    bool setLectureType(const std::string& courseName, const Lecture& lecture, Lecture::eType type);
    bool setLectureClassroom(const std::string& courseName, const Lecture& lecture, int roomNumber);
    bool setLectureLecturer(const std::string& courseName, const Lecture& lecture, const std::string& professorID);
    bool setLecturePractitioner(const std::string& courseName, const Lecture& lecture, const std::string& practitionerID);
    bool setLecturesPractice(const std::string& courseName, int lecID, int pracID);
    bool addStudentToLectureWaitingList(const std::string& courseName, const Lecture& lecture, const std::string& studentID);
    bool removeStudentFromLectureWaitingList(const std::string& courseName, const Lecture& lecture, const std::string& studentID);
    const Lecture* getLecture(const std::string& courseName, int lectureId);

    // Student
    bool addStudent(const Student& newStudent);
    bool removeStudent(const std::string& studentID);
    bool setStudentDepartment(const std::string& studentID, Student::eDepartmenType newDepartmentType);
    bool updateStudentGrade(const std::string& studentID, const Lecture& lecture, int newGrade);
    bool addLectureToStudent(const std::string& studentID, const Lecture& lecture);
    bool removeStudentFromCourse(const std::string& studentID, const std::string& courseName);
    const std::map<std::string, const Student *> getStudents() const;
    const Student* getStudentById(const std::string& id) const;
    void printStudents(std::ostream& os) const;
    void printProfessorsOfStudent(std::ostream& os, const std::string& id);

    // Professor
    bool addProfessor(const Professor& newProfessor);
    bool removeProfessor(const std::string& id);
    bool setProfesssorSalary(const std::string& id, double newSalary);
    bool addLectureToProfessor(const std::string& id, const Lecture* newLecture);
    bool removeLectureFromProfessor(const std::string& id, const Lecture* lectureToRemove);
    const std::map<std::string, const Professor*> getProfessors() const;
    const Professor* getProfessorById(const std::string& id) const;
    void printProfessors(std::ostream& os) const;
    void printProfessorsOfStudent(std::ostream& os, const std::string& id) const;
    int getNumOfProfessors() const;

    // Practitioner
    bool addPractitioner(const Practitioner& newPractitioner);
    bool removePractitioner(const std::string& id);
    bool setPractitionerSalary(const std::string& id, double newSalary);
    bool addPracticeToPractitioner(const std::string& id, const Lecture* newLecture);
    bool removePracticeFromPractitioner(const std::string& id, const Lecture* lectureToRemove);
    bool setPractitionerDepartment(const std::string& id, Student::eDepartmenType newDepartmentType);
    bool updatePractitionerGrade(const std::string& id, const Lecture& lecture, int newGrade);
    bool addLectureToPractitioner(const std::string& id, const Lecture& lecture);
    bool removePractitionerFromCourse(const std::string& id, const std::string& courseName);
    // return also the current number of professors
    const std::map<std::string, const Practitioner*> getPractitioners() const;
    const Practitioner* getPractitionerById(const std::string& id) const;
    void printPractitioners(std::ostream& os) const;    
    
    const College & operator+=(const Course & c);
    const College & operator+=(const Student & s);
    const College & operator+=(const Professor & p);
    const College & operator+=(const Practitioner & p);
    const College & operator+=(const ClassRoom & cr);

    const College & operator-=(const ClassRoom & cr);

    friend std::ostream & operator<<(std::ostream & os, const College & c);

    ~College();
private:
    College(const College & otherC) = delete;
    College(College&& otherC) = delete;
    College& operator=(const College& otherC) = delete;
    College & operator=(College && otherC) = delete;
    
    void removeProfessorFromAllCourses(Professor & professor);
    void removeStudentFromAllLectures(Student * removeStudent);
    void removeClassRoomFromAllLectures(const ClassRoom& c);
};
#endif