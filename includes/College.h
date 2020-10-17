#ifndef __H_COLLEGE__
#define __H_COLLEGE__

#include "Course.h"
#include "Person.h"
#include "Practitioner.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "ClassRoom.h"

class College
{
private:
    Student * *students;
    int maxStudents;
    int numOfStudents;

    Professor * *professors;
    int maxProfessors;
    int numOfProfessors;
    
    Practitioner * *practitioners;
    int maxPractitioners;
    int numOfPractitioners;
    
    Course * *courses;
    int maxCourses;
    int numOfCourses;
    
    ClassRoom * *classRooms;
    int maxClassRooms;
    int numOfClassRooms;

public:
    College(int maxAllStudents = 100, int maxAllProfessors = 100, int maxAllCourses = 100,
            int maxAllClassRooms = 100) noexcept(false);

    // ClassRoom
    bool addClassRoom(const ClassRoom& newClassroom);
    bool removeClassRoom(const ClassRoom& classRoomToRemove);
    const ClassRoom* getClassRoomByNumber(int roomNumber) const;
    const ClassRoom* const* getClassRooms(int* numOfClassRooms) const;
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
    const Course* const* getCourses(int* numOfCourses) const;
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
    const Student* const* getStudents(int* numOfStudents) const;
    const Student* getStudentById(const std::string& id) const;
    void printStudents(std::ostream& os) const;
    void printProfessorsOfStudent(std::ostream& os, const std::string& id);

    // Professor
    bool addProfessor(const Professor& newProfessor);
    bool removeProfessor(const std::string& id);
    bool setProfesssorSalary(const std::string& id, double newSalary);
    bool addLectureToProfessor(const std::string& id, const Lecture* newLecture);
    bool removeLectureFromProfessor(const std::string& id, const Lecture* lectureToRemove);
    const Professor* const* getProfessors(int* numOfProfessors) const;
    const Professor* getProfessorById(const std::string& id) const;
    void printProfessors(std::ostream& os) const;
    void printProfessorsOfStudent(std::ostream& os, const char* id) const;
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
    const Practitioner* const* getPractitioners(int* numOfPractitioners) const;
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

    bool removeStudent(int index);
    bool removePractitioner(int index);
    bool removeProfessor(int index);
    bool removeCourse(int index);
    bool removeClassRoom(int index);
    
    void removeProfessorFromAllCourses(Professor & professor);
    void removeStudentFromAllLectures(Student * removeStudent);
    void removeClassRoomFromAllLectures(const ClassRoom& c);

    int getStudentIndex(const std::string& id) const;
    int getPractitionerIndex(const std::string& id) const;
    int getProfessorIndex(const std::string& id) const;
    int getCourseIndex(const std::string& name) const;
    int getClassRoomIndex(int roomNumber) const;
};
#endif