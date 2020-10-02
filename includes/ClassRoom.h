#ifndef __H_CLASSROOM__
#define __H_CLASSROOM__

class ClassRoom
{
private:
	/******Attributes******/
	int roomNumber;
	int maxSeats;
public:
	/******Constructors******/
	ClassRoom(int roomNumber, int maxSeats);

	/******Gets/Sets******/
	int getRoomNumber() const { return roomNumber; }
	bool setRoomNumber(int newRoomNumber);
	int getMaxSeats()const { return maxSeats; }
	bool setMaxSeats(int newMaxSeats);

	/******print******/
	void print()const;

};
#endif
