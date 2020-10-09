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

std::ostream& operator<<(std::ostream& os, const ClassRoom& cr)
{
	os << "ClassRoom Number: " << cr.roomNumber << ", contains " << cr.maxSeats << " seats" << endl;
	return os;
}

