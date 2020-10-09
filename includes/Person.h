#ifndef __H_PERSON__
#define __H_PERSON__

#include <iostream>
#include "Date.h"

class Person
{
private:
	char* name;
	char* id;
	const Date *birthDate;

public:
	static const  int NAME_LEN = 20;
	static const int ID_LEN = 10;

	Person(const char* name, const Date& birthDate, const char* id) noexcept;
	Person(const Person& other) noexcept;
	Person(Person&& other) noexcept;

	virtual Person& operator=(const Person& other);
	virtual Person& operator=(Person&& other) noexcept;

	virtual ~Person();

	const char* getName() const { return name; }
	const Date& getBirthDate() const { return *birthDate; }
	const char* getId() const { return id; }

	friend std::ostream& operator<<(std::ostream& os, const Person& per);
	virtual void print(std::ostream& os) const;

	virtual bool operator==(const char* id) const;
	virtual bool operator==(Person& other) const;
};

#endif /* __H_PERSON__ */
