#ifndef __H_PERSON__
#define __H_PERSON__

#include <iostream>
#include "Date.h"

class Person
{
private:
	char* name;
	char* id;
	Date* birthDate;

public:
	Person(const char* name, const Date& birthDate, const char* id) noexcept(false);
	Person(const Person& other) noexcept;
	Person(Person&& other) noexcept;

	virtual Person& operator=(const Person& other);
	virtual Person& operator=(Person&& other) noexcept;

	virtual ~Person();

	bool setName(const char* name);
	const char* getName() const { return name; }

	bool setId(const char* id);
	const char* getId() const { return id; }

	void setBirthDate(const Date& date);
	const Date& getBirthDate() const { return *birthDate; }

	friend std::ostream& operator<<(std::ostream& os, const Person& per);
	virtual void print(std::ostream& os) const;

	virtual bool operator==(const char* id) const;
	virtual bool operator==(const Person& other) const;
};

#endif /* __H_PERSON__ */
