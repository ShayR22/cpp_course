#ifndef __H_PERSON__
#define __H_PERSON__

using namespace std;
#include <iostream>

#include "Date.h"


class Person
{
public://public methods
	static const  int NAME_LEN = 20;
	static const int ID_LEN = 10;
private:
	/******Attributes******/
	char name[NAME_LEN];
	char id[ID_LEN];
	Date birthDate;

public://public methods
	/******Constructors******/
	Person(const char* name, const Date& birthDate, const char* id);//Constructor
	virtual ~Person();

	/******Gets/Sets******/
	const char* getName() const { return name; }
	const Date& getBirthDate() const { return birthDate; }// return the obj or the address
	const char* getId() const { return id; }
	bool setName(const char* newName);

	/******print******/
	friend ostream& operator<<(ostream& os, Person& per); // for good impelemtation, use 'print' here, to print professors and students
	virtual void print(ostream& os) const;						//	instead of add operator<< to students and professors

	virtual bool operator==(const char* id) const;	//	equal a Person obj by ID string
	
private://private methods

	/******Gets/Sets******/
	bool setBirthDate(const Date& newBirthDate);
	bool setId(const char* newId);
};


#endif 
