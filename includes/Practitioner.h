#ifndef __H_PRACTITIONER__
#define __H_PRACTITIONER__

#include "Professor.h"
#include "Student.h"

class Practitioner : public Professor, public Student
{
public:
	Practitioner(const char* name, const Date& birthDate, const char* id, eDepartmenType department, double salary,
		int maxOfGrades = 20, int maxOfLectures = 20, int maxOfLecturesTeaching = 5) noexcept(false);
	Practitioner(Professor& p, Student& s) noexcept(false); // check that p and s are the same person

	const Professor** assistantTo(int* proffesors_size) const; //To whom he helps

	/******print******/
	virtual void print(ostream& os) const;

private:
	Practitioner(const Practitioner& otherP) = delete;
	Practitioner(Practitioner&& otherP) = delete;
	Practitioner& operator=(const Practitioner& otherP) = delete;
	Practitioner& operator=(Practitioner&& otherP) = delete;
};
#endif