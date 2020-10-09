#include "Practitioner.h"

using namespace std;

/* TODO maxOfLecturesTeaching isn't being used */
Practitioner::Practitioner(const char* name, const Date& birthDate, const char* id, eDepartmenType department, double salary,
	int maxOfGrades, int maxOfLectures, int maxOfLecturesTeaching) noexcept(false) :
	Person(name, birthDate, id),
	Professor(name, birthDate, id, salary, maxOfLectures),
	Student(name, birthDate, id, department, maxOfGrades) {}

Practitioner::Practitioner(Professor& p, Student& s) noexcept(false) :
	Professor(p.getName(), p.getBirthDate(), p.getId(), p.getSalary()),
	Student(s.getName(), s.getBirthDate(), s.getId(), s.getDepartment()),
	Person(p.getName(), p.getBirthDate(), p.getId())
{
	if (!(s == p.getId()))
		throw -1;
}

Practitioner::Practitioner(const Practitioner& other) noexcept: Person(other), Student(other), Professor(other) {}
Practitioner::Practitioner(Practitioner&& other) noexcept: Person(other), Student(other), Professor(other) {}

const Professor** Practitioner::assistantTo(int *proffesors_size) const
{
	int numLectures;
	const Lecture* const* lectures = getLectures(&numLectures);
	if (numLectures == 0)
		return nullptr;

	const Professor** assistingTo = new const Professor * [numLectures];
	for (int i = 0; i < numLectures; i++)
		assistingTo[i] = &lectures[i]->getLecturer();

	*proffesors_size = numLectures;

	return assistingTo;
}

void Practitioner::print(ostream& os) const
{
	Professor::print(os);
	Student::print(os);
}

Practitioner& Practitioner::operator=(const Practitioner& other)
{
	Student::operator=(other);
	Professor::operator=(other);
	Person::operator=(other);
	return *this;
}
Practitioner& Practitioner::operator=(Practitioner&& other) noexcept
{
	Student::operator=(other);
	Professor::operator=(other);
	Person::operator=(other);
	return *this;
}