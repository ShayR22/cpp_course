#include "Practitioner.h"

Practitioner::Practitioner(const char* name, const Date& birthDate, const char* id, eDepartmenType department, double salary,
	int maxOfGrades, int maxOfLectures, int maxOfLecturesTeaching) :
	Professor(name, birthDate, id ,salary, maxOfLectures), Student(name, birthDate, id, department, maxOfGrades)
{

}

Practitioner::Practitioner(Professor& p, Student& s) :
	Professor(p.getName(), p.getBirthDate(), p.getId(), p.getSalary()),
	Student(s.getName(), s.getBirthDate(), s.getId(), s.getDepartment())
{

}
 // check that p and s are the same person
	

const Professor** Practitioner::assistantTo() const
{
	return nullptr;
}

void Practitioner::print(ostream& os) const
{

}

Practitioner::~Practitioner()
{

}
