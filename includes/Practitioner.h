#ifndef __H_PRACTITIONER__
#define __H_PRACTITIONER__

#include "Professor.h"
#include "Student.h"

class Practitioner : public Professor, public Student
{
public:
	Practitioner(const char* name, const Date& birthDate, const char* id, eDepartmenType department, double salary,
		int maxOfGrades = 20, int maxOfLectures = 20, int maxOfLecturesTeaching = 5) noexcept(false);
	Practitioner(Professor& p, Student& s) noexcept(false);
	Practitioner(const Practitioner& other) noexcept;
	Practitioner(Practitioner&& other) noexcept;

	const Professor** assistantTo(int* proffesors_size) const;

	virtual void print(std::ostream& os) const;

	Practitioner& operator=(const Practitioner& other);
	Practitioner& operator=(Practitioner&& other) noexcept;
};
#endif