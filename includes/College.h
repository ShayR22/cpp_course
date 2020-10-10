#ifndef __H_COLLEGE__
#define __H_COLLEGE__

#include "Course.h"
#include "Person.h"
#include "Practitioner.h" // need to check where put this include
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
    College(int maxAllStudents = 100, int maxAllProfessors = 100, int maxAllCourses = 100, int maxAllClassRooms = 100) noexcept(false);

    // ClassRoom
    bool addClassRoom(const ClassRoom& newClassroom);
    bool removeClassRoom(const ClassRoom& classRoomToRemove);
    const ClassRoom* getClassRoomByNumber(int roomNumber) const;
    const ClassRoom* const* getClassRooms(int* numOfClassRooms) const;
    void printClassRooms(std::ostream& os) const;

    // Course
    bool addCourse(const Course& newCourse);
    bool removeCourse(const Course& courseToRemove);
    bool setCourseName(const char* name, const char* newName);
    bool setCoursePoints(const char* name, float points);
    bool addNewLectureToCourse(const char* courseName, const Lecture& newLecture);
    bool removeLectureFromCourse(const char* courseName, int id);
    bool addConditionCourseToCourse(const char* name, const Course& c);
    bool removeConditionCourseFromCourse(const char *name, const char *remove);
    const Course* const* getCourses(int* numOfCourses) const;
    const Course* getCourseByName(const char* name) const;
    void printCourses(std::ostream& os) const;

    // Lecture
    bool addLectureToCourse(const Lecture& lecture, const char* courseName);
    bool removeLectureFromCourse(const Lecture& lecture, const char* courseName);
    bool setLectureWeekDay(const char* courseName, const Lecture& lecture, Lecture::eWeekDay day);
    bool setLecturStartHour(const char* courseName, const Lecture& lecture, int hour);
    bool setLectureDuration(const char* courseName, const Lecture& lecture, int durationHours);
    bool setMaxStudentList(const char* courseName, const Lecture& lecture, int newMaxStudents);
    bool setLectureType(const char* courseName, const Lecture& lecture, Lecture::eType type);
    bool setLectureClassroom(const char* courseName, const Lecture& lecture, int roomNumber);
    bool setLectureLecturer(const char* courseName, const Lecture& lecture, const char *professorID);
    bool setLecturePractitioner(const char* courseName, const Lecture& lecture, const char* practitionerID);
    bool addStudentToLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID);
    bool removeStudentFromLectureWaitingList(const char* courseName, const Lecture& lecture, const char* studentID);

    // Student
    bool addStudent(const Student& newStudent);
    bool removeStudent(const char* studentID);
    bool setStudentDepartment(const char* studentID, Student::eDepartmenType newDepartmentType);
    bool updateStudentGrade(const char* studentID, const Lecture& lecture, int newGrade);
    bool addLectureToStudent(const char* studentID, const Lecture& lecture);
    bool removeStudentFromCourse(const char* studentID, const char* courseName);
    const Student* const* getStudents(int* numOfStudents) const;
    const Student* getStudentById(const char* id) const;
    void printStudents(std::ostream& os) const;

    // Professor
    bool addProfessor(const Professor& newProfessor);
    bool removeProfessor(const char* id);
    bool setProfesssorSalary(const char* id, double newSalary);
    bool addLectureToProfessor(const char* id, const Lecture* newLecture);
    bool removeLectureFromProfessor(const char* id, const Lecture* lectureToRemove);
    const Professor* const* getProfessors(int* numOfProfessors) const;
    const Professor* getProfessorById(const char* id) const;
    void printProfessors(std::ostream& os) const;

    // Practitioner
    bool addPractitioner(const Practitioner& newPractitioner);
    bool removePractitioner(const char *id);
    bool setPractitionerSalary(const char* id, double newSalary);
    bool addPracticeToPractitioner(const char* id, const Lecture* newLecture);
    bool removePracticeFromPractitioner(const char* id, const Lecture* lectureToRemove);
    bool setPractitionerDepartment(const char* id, Student::eDepartmenType newDepartmentType);
    bool updatePractitionerGrade(const char* id, const Lecture& lecture, int newGrade);
    /* TODO give better name from the student fucntions of practitioner */
    bool addLectureToPractitioner(const char* id, const Lecture& lecture);
    bool removePractitionerFromCourse(const char* id, const char* courseName);
    // return also the current number of professors
    const Practitioner* const* getPractitioners(int* numOfPractitioners) const;
    const Practitioner* getPractitionerById(const char* id) const;
    void printPractitioners(std::ostream& os) const;

    const College & operator+=(Course & c);
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

    int getStudentIndex(const char* id) const;
    int getPractitionerIndex(const char* id) const;
    int getProfessorIndex(const char* id) const;
    int getCourseIndex(const char* name) const;
    int getClassRoomIndex(int roomNumber) const;
};
#endif