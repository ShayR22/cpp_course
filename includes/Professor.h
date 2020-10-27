#ifndef __H_PROFESSOR__
#define __H_PROFESSOR__

#include "Person.h"
#include "Course.h"

class Professor : virtual public Person
{
private:
	double salary;
	const Lecture** lectures;
	int maxOfLectures;
	int numOfLectures;
	void removeLectureByIndex(int index);
	int getLectureIndex(const Lecture& find);

protected:
	virtual void printAddition(std::ostream& os) const;

public:
	Professor(const char* name, const Date& birthDate, const char* id, double salary, int maxOfLectures = 5) noexcept(false);
	Professor(const Professor& other) noexcept;
	Professor(Professor&& other) noexcept;
	
	const Professor& operator=(const Professor& other);
	const Professor& operator=(Professor& other) noexcept;

	~Professor();

	bool setSalary(double new_salary);
	double getSalary() const { return salary; }
	inline const Lecture * const* getLectures(int* numOfLectures) const;

	bool removeLecture(const Lecture* lectureToRemove);
	bool addLectureTeaching(const Lecture* newLecture);

	void printLectures(std::ostream& os) const;
	void printLecturesNames(std::ostream& os) const;
	virtual void print(std::ostream& os) const;

	const Professor& operator+=(const Lecture& l);
	const Professor& operator-=(const Lecture& l);
};

const Lecture* const* Professor::getLectures(int* numOfLectures) const
{
	*numOfLectures = this->numOfLectures;
	return lectures;
}

#endif /* __H_PROFESSOR__ */