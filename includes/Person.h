#ifndef __H_PERSON__
#define __H_PERSON__

#include <iostream>
#include "Date.h"

class Person
{
private:
	std::string name;
	std::string id;
	Date* birthDate;

public:
	Person(const std::string& name, const Date& birthDate, const std::string& id) noexcept(false);
	Person(const Person& other) noexcept;
	Person(Person&& other) noexcept;

	virtual Person& operator=(const Person& other);
	virtual Person& operator=(Person&& other) noexcept;

	virtual ~Person();

	bool setName(const std::string& name);
	const std::string& getName() const { return name; }

	bool setId(const std::string& id);
	const std::string& getId() const { return id; }

	void setBirthDate(const Date& date);
	const Date& getBirthDate() const { return *birthDate; }

	friend std::ostream& operator<<(std::ostream& os, const Person& per);
	virtual void print(std::ostream& os) const;

	virtual bool operator==(const std::string& id) const;
	virtual bool operator==(const Person& other) const;
};

#endif /* __H_PERSON__ */
