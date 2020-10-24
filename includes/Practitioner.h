#ifndef __H_PRACTITIONER__
#define __H_PRACTITIONER__

#include "Professor.h"
#include "Student.h"
#include <map>

class Practitioner : public Professor, public Student
{
public:
	Practitioner(const std::string& name, const Date& birthDate, const std::string& id, eDepartmenType department,
				 double salary, int maxOfLectures = 20, int maxOfLecturesTeaching = 5) noexcept(false);
	Practitioner(Professor& p, Student& s) noexcept(false);
	Practitioner(const Practitioner& other) noexcept;
	Practitioner(Practitioner&& other) noexcept;

	Practitioner& operator=(const Practitioner& other);
	Practitioner& operator=(Practitioner&& other) noexcept;

	const std::map<std::string, const Professor*> assistantTo() const;

	virtual void printAddition(std::ostream& os) const;
	virtual void print(std::ostream& os) const;
};

#endif /* __H_PRACTITIONER__ */
