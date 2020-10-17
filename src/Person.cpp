#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Person.h"
#include <string>

using namespace std;

Person::Person(const string& name, const Date& birthDate, const string& id) noexcept(false) :
	birthDate(nullptr)
{
	if (!setName(name))
		throw "Error: name have to have length of at least 1";
	if (!setId(id))
		throw "Error: id have to have length of at least 1";

	this->birthDate = new Date(birthDate);
}

Person::Person(const Person& other) noexcept:
	birthDate(nullptr)
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

	this->name = other.name;
	this->id = other.id;
	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	this->birthDate = other.birthDate;
	other.birthDate = nullptr;
	this->name = move(other.name);
	this->id = move(other.id);
	return *this;
}

Person::~Person()
{
	delete birthDate;
}

bool Person::setName(const string& name)
{
	if (name.empty())
	{
		cout << "name cant be empty";
		return false;
	}

	this->name = name;
	return true;
}

bool Person::setId(const string& id)
{
	if (id.empty())
	{
		cout << "id cant be null";
		return false;
	}

	this->id = id;
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

bool Person::operator==(const string& id) const
{
	return this->id == id;
}

bool Person::operator==(const Person& other) const
{
	return (*this == other.id);
}
