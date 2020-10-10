#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "College.h"

#define COURSE_NAME_SIZE 20

using namespace std;

static int printMenu(College& c)
{
	/* TODO FIXME */
	return -1;
}

int main(int argc, char** argv)
{
	College* college = new College();

	//	TODO: load classes from file		////////////////////////////////////////
	//	TODO: load practitioners from file	////////////////////////////////////////

	char choice = '0';
	do
	{
		choice = printMenu(*college);
	} while (choice != 'q');

	return 0;
}