#include "Practitioner.h"

using namespace std;

Practitioner::Practitioner(const char* name, const Date& birthDate, const char* id, eDepartmenType department,
						   double salary, int maxOfLectures, int maxOfLecturesTeaching) noexcept(false) :
	Person(name, birthDate, id),
	Professor(name, birthDate, id, salary, maxOfLecturesTeaching),
	Student(name, birthDate, id, department, maxOfLectures) {}

Practitioner::Practitioner(Professor& p, Student& s) noexcept(false) :
	Person(p),
	Professor(p),
	Student(s)
{
	if (!(s == p))
		throw "Error not the same Person has been given to professor and student";
}

Practitioner::Practitioner(const Practitioner& other) noexcept: Person(other), Student(other), Professor(other) {}
Practitioner::Practitioner(Practitioner&& other) noexcept: Person(other), Student(other), Professor(other) {}

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

const map<string, const Professor*> Practitioner::assistantTo() const
{
	map<string, const Professor*> professors;
	const map<int, const Lecture*> lectures = getLectures();

	for (auto& e : lectures) {
		const Professor& professor = e.second->getLecturer();
		professors[professor.getId()] = &professor;
	}

	return professors;
}

void Practitioner::printAddition(ostream& os) const
{
	printLecturesNames(os); 
}

void Practitioner::print(ostream& os) const
{
	os << "Prctitioner info:" << endl;
	Person::print(os);
	printAddition(os);
}