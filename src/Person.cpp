#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Person.h"
#include <string>

using namespace std;

Person::Person(const char* name, const Date& birthDate, const char* id) noexcept(false) :
	name(nullptr), id(nullptr), birthDate(nullptr)
{
	if (!setName(name))
		throw "Error: name cant be null and have to have length of at least 1";
	if (!setId(id))
		throw "Error: id cant be null and have to have length of at least 1";

	this->birthDate = new Date(birthDate);
}

Person::Person(const Person& other) noexcept:
	name(nullptr), id(nullptr), birthDate(nullptr)
{
	*this = other;
}

Person::Person(Person&& other) noexcept :
	name(nullptr), id(nullptr), birthDate(nullptr)
{
	*this = other;
}

Person& Person::operator=(const Person& other)
{
	if (this->birthDate)
		*(this->birthDate) = *(other.birthDate);
	else
		this->birthDate = new Date(*other.birthDate);

	setName(other.name);
	setId(other.id);
	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	this->birthDate = other.birthDate;
	other.birthDate = nullptr;

	this->name = other.name;
	other.name = nullptr;

	this->id = other.id;
	other.id = nullptr;

	return *this;
}

Person::~Person()
{
	delete name;
	delete id;
	delete birthDate;
}

bool Person::setName(const char* name)
{
	if (!name)
	{
		cout << "name cant be null";
		return false;
	}
	else if (strlen(name) <= 0)
	{
		cout << "name must be positive length";
		return false;
	}

	delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	return true;
}

bool Person::setId(const char* id)
{
	if (!id)
	{
		cout << "id cant be null";
		return false;
	}
	else if (strlen(id) <= 0)
	{
		cout << "id must be positive length";
		return false;
	}

	delete this->id;
	this->id = new char[strlen(id) + 1];
	strcpy(this->id, id);
	return true;
}

void Person::setBirthDate(const Date& date)
{
	if (this->birthDate)
		*(this->birthDate) = date;
	else
		this->birthDate = new Date(date);
}

void Person::print(ostream& os) const
{
	os << name << "(id:" << id << "), " << *birthDate;
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
