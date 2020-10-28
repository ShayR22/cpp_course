#ifndef __H_PROFESSOR__
#define __H_PROFESSOR__

#include "Person.h"
#include "Course.h"

class Professor : virtual public Person
{
private:
	double salary;
	std::map<int, const Lecture*> lectures;
	int maxOfLectures;

protected:
	virtual void printAddition(std::ostream& os) const;

public:
	Professor(const std::string& name, const Date& birthDate, const std::string& id, double salary, int maxOfLectures = 5) noexcept(false);
	Professor(const Professor& other) noexcept;
	Professor(Professor&& other) noexcept;
	
	const Professor& operator=(const Professor& other);
	const Professor& operator=(Professor&& other) noexcept;

	bool setSalary(double new_salary);
	double getSalary() const { return salary; }
	const std::map<int, const Lecture*> getLectures() const { return lectures; };

	bool removeLecture(const Lecture* lectureToRemove);
	bool addLectureTeaching(const Lecture* newLecture);

	void printLectures(std::ostream& os) const;
	void printLecturesNames(std::ostream& os) const;
	virtual void print(std::ostream& os) const;

	const Professor& operator+=(const Lecture& l);
	const Professor& operator-=(const Lecture& l);

	~Professor();
};

#endif /* __H_PROFESSOR__ */