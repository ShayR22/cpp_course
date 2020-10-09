#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Person.h"
#include <string>

using namespace std;

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

Person::Person(const char* name, const Date& birthDate, const char* id) noexcept : birthDate(&birthDate)
{
	this->name = new char[NAME_LEN];
	this->id = new char[ID_LEN];
	this->birthDate = new Date(birthDate);

	/* -1 in order to save 1 index for '\0' */
	setNameOrZeros(this->name, name, (Person::NAME_LEN - 1));
	setNameOrZeros(this->id, id, (Person::ID_LEN - 1));
}

Person::Person(const Person& other) noexcept
{
	*this = other;
}

Person::Person(Person&& other) noexcept
{
	*this = other;
}

Person& Person::operator=(const Person& other)
{
	this->birthDate = other.birthDate;

	/* -1 in order to save 1 index for '\0' */
	setNameOrZeros(this->name, other.name, (Person::NAME_LEN - 1));
	setNameOrZeros(this->id, other.id, (Person::ID_LEN - 1));
	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	this->birthDate = other.birthDate,
		this->name = other.name;
	this->id = other.id;

	other.name = nullptr;
	other.id = nullptr;
	other.birthDate = nullptr;
	return *this;
}

Person::~Person()
{
	delete name;
	delete id;
	delete birthDate;
}

void Person::print(ostream& os) const
{
	os << name << "(" << id << "), " << birthDate << endl;
}

ostream& operator<<(ostream& os, const Person& per)
{
	per.print(os);
	return os;
}

bool Person::operator==(const char* id) const
{
	if (!strcmp(this->id, id))
		return true;
	return false;
}

bool Person::operator==(const Person& other) const
{
	return (*this == other.id);
}
