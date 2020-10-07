#include <string.h>
#include "Person.h"

#define _CRT_SECURE_NO_WARNINGS

static void setNameOrZeros(char* dest, const char* src, int dest_len)
{
	if (src)
	{
		strncpy(dest, src, (dest_len - 1));
		dest[dest_len] = '\0';
		return;
	}
	memset(dest, 0, dest_len);
}

Person::Person(const char* name, const Date& birthDate, const char* id) :
	birthDate(birthDate)
{
	setNameOrZeros(this->name, name, (Person::NAME_LEN - 1));
	setNameOrZeros(this->id, id, (Person::ID_LEN - 1));
}

Person::~Person()
{

}

bool Person::setName(const char* newName)
{
	if (newName == nullptr)
		return false;
	else if (strlen(newName) >= Person::NAME_LEN)
		return false;

	setNameOrZeros(name, newName, Person::NAME_LEN);
	return true;
}

ostream& operator<<(ostream& os, Person& per)
{
	per.print(os);
	return os;
}

void Person::print(ostream& os) const
{
	os << name << "(" << id << ")";
	os << ", Birthday: ";
	/* TODO need to add for Date ostream operator or change print to get ostream */
	birthDate.print();
}

bool Person::operator==(const char* id) const
{
	if (!strcmp(this->id, id))
		return true;
	return false;
}

void Person::setBirthDate(const Date& newBirthDate)
{
	birthDate = newBirthDate;
}
bool Person::setId(const char* newId)
{
	if (!newId)
		return false;
	else if (strlen(newId) >= Person::ID_LEN)
		return false;
	setNameOrZeros(id, newId, Person::ID_LEN);
	return true;

}
