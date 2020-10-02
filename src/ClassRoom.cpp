#include "ClassRoom.h"
#include <iostream>

using namespace std;

ClassRoom::ClassRoom(int roomNumber, int maxSeats) :
	roomNumber(roomNumber), maxSeats(maxSeats) {}

bool ClassRoom::setRoomNumber(int newRoomNumber)
{
	if (newRoomNumber < 0)
		return false;

	roomNumber = newRoomNumber;
	return true;
}
bool ClassRoom::setMaxSeats(int newMaxSeats)
{
	if (newMaxSeats < 0)
		return false;

	maxSeats = newMaxSeats;
	return true;
}

void ClassRoom::print() const
{
	cout << "ClassRoom Number: " << roomNumber << ", contains " << maxSeats << " seats" << endl;
}

