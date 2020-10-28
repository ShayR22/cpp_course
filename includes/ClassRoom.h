#ifndef __H_CLASSROOM__
#define __H_CLASSROOM__

#include <iostream>

class ClassRoom
{
private:
	int roomNumber;
	int maxSeats;
public:
	ClassRoom(int roomNumber, int maxSeats);

	bool operator==(const ClassRoom& other) const;
	bool operator==(int roomNumber) const;

	int getRoomNumber() const { return roomNumber; }
	bool setRoomNumber(int newRoomNumber);
	int getMaxSeats()const { return maxSeats; }
	bool setMaxSeats(int newMaxSeats);

	friend std::ostream& operator<<(std::ostream& os, const ClassRoom& cr);
};
#endif
