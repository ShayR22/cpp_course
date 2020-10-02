#include "Person.h"

Person::Person(const char* name, const Date& birthDate, const char* id) :
	birthDate(birthDate)
{

}

Person::~Person()
{

}

bool Person::setName(const char* newName)
{
	return false;
}


ostream& operator<<(ostream& os, Person& per)
{
	return os;
}


void Person::print(ostream& os) const
{

}

bool Person::operator==(const char* id) const
{
	return false;
} // equal a Person obj by ID string
	

bool Person::setBirthDate(const Date& newBirthDate)
{
	return false;
}
bool Person::setId(const char* newId)
{
	return false;
}


