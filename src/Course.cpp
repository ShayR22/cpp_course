#define _CRT_SECURE_NO_WARNINGS

#include <ostream>
#include <string>
#include <cmath>
#include "Professor.h"
#include "Course.h"
#include "Student.h"

#define EPSSILON 0.0000001

using namespace std;

Course::Course(const string& name, const Professor* coordinator, float points,
	int maxLectures, int maxConditionCourses) : 
	coordinator(coordinator), maxLectures(maxLectures), maxConditionCourses(maxConditionCourses)
{
	if (!setCourseName(name))
		throw "ERROR: In class Course: name is nullptr";
	
	if(!setPoints(points))
		throw "ERROR: In class Course: points can't be negative or not divisible by 0.5";
}

Course::Course(const Course& other) noexcept :
	coordinator(nullptr)
{
	*this = other;
}

Course::Course(Course&& other) noexcept :
	coordinator(nullptr)
{
	*this = other;
}

Course& Course::operator=(const Course& other) noexcept
{
	setCourseName(other.name);
	coordinator = other.coordinator;
	points = other.points;

	maxLectures = other.maxLectures;

	map<int, Lecture*>::const_iterator it = other.lectures.begin();
	while (it != other.lectures.end())
	{
		lectures[it->first] = new Lecture(*(it->second));
		++it;
	}

	maxConditionCourses = other.maxConditionCourses;
	conditionCourses = other.conditionCourses;

	return *this;
}

Course& Course::operator=(Course&& other) noexcept
{
	name = other.name;
	coordinator = other.coordinator;
	other.coordinator = nullptr;
	points = other.points;

	maxLectures = other.maxLectures;
	other.maxLectures = 0;

	for (auto& e : other.lectures)
	{
		lectures[e.first] = e.second;
		e.second = nullptr;
	}

	map<int, Lecture*>::iterator it;
	lectures.erase(it = lectures.begin(), lectures.end());

	maxConditionCourses = other.maxConditionCourses;
	other.maxConditionCourses = 0;
	conditionCourses = other.conditionCourses;
	
	return *this;
}

bool Course::operator==(const Course& other) const
{
	return name == other.name;
}

bool Course::operator==(const string& name) const
{
	return this->name == name;
}

bool Course::setCourseName(const string& newCourseName)
{
	if (newCourseName.empty())
	{
		cout << "course name cant be empty" << endl;
		return false;
	}

	this->name = newCourseName;
	return true;
}

bool Course::setCoordinator(const Professor* p)
{
	if (p == nullptr)
		return false;

	coordinator = p;
	return true;
}

bool Course::setPoints(float p)
{
	const double epsilon = 1e-6;
	float remainder = p - (long)p;

	if (p < 0 || (remainder > epsilon && remainder - 0.5 > epsilon))
		return false;

	points = ((int)((p + epsilon) * 2)) / 2.f;

	return true;
}

bool Course::removeLecture(const Lecture& lectureToRemove)
{
	return removeLecture(lectureToRemove.getId());
}

bool Course::removeLecture(int id)
{
	if (!lectures.erase(id))
	{
		cout << "Lecture was not found, remove failed" << endl;
		return false;
	}
	return true;
}

bool Course::addLecture(const Lecture& lectureToAdd)
{
	if (lectures.size() >= (unsigned int)maxLectures)
	{
		cout << "Course is full, can't add more lectures" << endl;
		return false;
	}

	if (lectures.find(lectureToAdd.getId()) != lectures.end())
	{
		cout << "lecture is already inside the course" << endl;
		return false;
	}

	lectures[lectureToAdd.getId()] = new Lecture(lectureToAdd);
	return true;
}

bool Course::removeConditionCourse(const Course& c)
{
	return removeConditionCourse(c.getCourseName());
}

bool Course::removeConditionCourse(const string& name)
{
	if (!conditionCourses.erase(name))
	{
		cout << "Course was not found" << endl;
		return false;
	}
	return true;
}

bool Course::addConditionCourse(const Course& c)
{
	if (conditionCourses.size() >= (unsigned int)maxConditionCourses)
		return false;

	if (conditionCourses.find(c.getCourseName()) != conditionCourses.end())
	{
		cout << "lecture is already inside the course" << endl;
		return false;
	}

	conditionCourses[c.getCourseName()] = &c;
	return true;
}

const Lecture* Course::getLectureById(int lectureId) const
{
	map<int, Lecture*>::const_iterator pos = lectures.find(lectureId);
	if (pos == lectures.end())
		return nullptr;
	return pos->second;
}

bool Course::setLectureWeekDay(const Lecture& lecture, Lecture::eWeekDay day)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}

	lectures[lecture.getId()]->setWeekDay(day);
	return true;
}

bool Course::setLecturStartHour(const Lecture& lecture, int hour)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}
	return lectures[lecture.getId()]->setHour(hour);
}

bool Course::setLectureDuration(const Lecture& lecture, int durationHours)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}
	return lectures[lecture.getId()]->setDuration(durationHours);
}

bool Course::setLectureMaxStudents(const Lecture& lecture, int newMaxStudents)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}
	return lectures[lecture.getId()]->setMaxStudentsMap(newMaxStudents);
}

bool Course::setLectureType(const Lecture& lecture, Lecture::eType type)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}

	lectures[lecture.getId()]->setLectureType(type);
	return true;
}

// Assumption: classroom is valid
bool Course::setLectureClassroom(const Lecture& lecture, const ClassRoom* classRoom)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}

	lectures[lecture.getId()]->setClassRoom(classRoom);
	return true;
}

// Assumption: professor is valid
bool Course::setLectureLecturer(const Lecture& lecture, const Professor* lecturer)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}

	lectures[lecture.getId()]->setLecturer(*lecturer);
	return true;
}

bool Course::addStudentToWaitingListCourse(const Lecture& lecture, const Student& student)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}
	return lectures[lecture.getId()]->addToWaitingMap(student);
}

// Assumption: student is valid
bool Course::removeStudentToWaitingListCourse(const Lecture& lecture, const Student& student)
{
	if (lectures.find(lecture.getId()) == lectures.end())
	{
		cout << "lecture not found" << endl;
		return false;
	}
	return lectures[lecture.getId()]->removeFromWaitingMap(student);
}

bool Course::setLecturePractice(int lectureID, int practiceID)
{
	if (lectures.find(lectureID) == lectures.end() ||
		lectures.find(practiceID) == lectures.end())
	{
		cout << "invalid lecture / practice have been given" << endl;
		return false;
	}

	if (lectures[lectureID]->getLectureType() != Lecture::eType::LECTURE ||
		lectures[practiceID]->getLectureType() != Lecture::eType::PRACTICE)
	{
		cout << "lecture given must be a lecture, and practice must be practice" << endl;
		return false;
	}

	Lecture* lecture = lectures.find(lectureID)->second;
	Lecture* practice = lectures.find(practiceID)->second;

	if (checkIfHourOverlap(*lecture, *practice))
		return false;

	lectures[lectureID]->setPracticeLecture(*lectures[practiceID]);
	return true;
}

bool Course::checkIfHourOverlap(const Lecture& lecture,const Lecture& practice)
{
	if (practice.getWeekDay() == lecture.getWeekDay())
	{
		int pHour = practice.getHour();
		int pDuration = practice.getDuration();
		int lHour = lecture.getHour();
		int lDuration = lecture.getDuration();
		if ((pHour > lHour&& lHour + lDuration > pHour) ||
			(lHour > pHour&& pHour + pDuration > lHour))
		{
			cout << "Invalid hours" << endl;
			return true;
		}
	}
	return false;
}

Course::eAddingStudentStatus Course::addStudentToCourse(const Lecture& lectureToEnter, Student& studentToSign) noexcept(false)
{
	if (lectures.find(lectureToEnter.getId()) == lectures.end())

		throw "ERROR: Lecture is not in course";

	if (!studentToSign.qualify(*this))
		return Course::eAddingStudentStatus::UNQUALIFIED;

	if (!lectures[lectureToEnter.getId()]->addStudent(studentToSign))
		return Course::eAddingStudentStatus::FULL;

	if (!studentToSign.addLecture(&lectureToEnter))
	{
		studentToSign.deleteFromCourse(*this);
		return Course::eAddingStudentStatus::FULL;
	}

	return Course::eAddingStudentStatus::SUCCESS;
}

bool Course::removeStudentFromCourse(const Student& student)
{
	for (auto& e : lectures)
		if (e.second->removeStudent(student))
			return true;
	return false;
}

void Course::printStudentsInCourse(ostream& os) const
{
	map<string, const Student*> totalStudentMap;
	
	for (auto& e : lectures)
	{
		const map<string, const Student*> studentMap = e.second->getStudentMap();
		for (auto& s : studentMap)
			totalStudentMap[s.first] = s.second;
	}

	for (auto& e : totalStudentMap)
		os << *e.second;
}

ostream& operator<<(ostream& os, const Course& c)
{
	os << "Course Name is " << c.name << endl;
	os << "coordinator is " << *(c.coordinator) << endl;
	os << "number of points is " << c.points << endl;

	os << "Lectures: " << (c.lectures.size() == 0 ? "No lectures" : "") << endl;
	int index = 0;
	for (auto& e : c.lectures)
		os << "(" << ++index << ") " << *(e.second);

	os << "Condition courses: " << (c.conditionCourses.size() == 0 ? "No condition courses" : "") << endl;
	index = 0;
	for (auto& e : c.conditionCourses)
		os << "(" << ++index << ") " << e.second->name;
	return os << "---------------------------------------" << endl;
}

Course::~Course() 
{
	map<int, Lecture*>::iterator it;
	lectures.erase(it = lectures.begin(), lectures.end());
}