#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "Coordinates.hpp"
#include "Options.hpp"

class Board
{
public:
	static Board* getInstance();
	~Board() {};

	void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
	void resetEverySlot();
	void resetSlot(const Coordinates& COORDINATES);

	const bool addNewCharacter(const Coordinates& COORDINATES, const Participant& PLAYER);

	void printBoard() const;
	const Participant findWinner() const;
	std::vector<Coordinates> getEveryEmptySlotCoordinates() const;
	const int getQuantityOfTakenSlots() const;
	const bool isAnyEmptySlot() const;
	const bool isSlotEmpty(const Coordinates& COORDINATES) const;

private:
	std::vector<std::vector<char>> board;
	int quantityOfTakenSlots;

	Options *gameOptionsManager = Options::getInstance();

	// Singleton
	static Board *instance;
	Board();
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;


	// TODO: implement algorithm with multi threads.
// EAST:
	const bool isPossibleToCheckEastSlots(const Coordinates& COORDINATES) const;
	const bool areEastSlotsNotEmpty(const Coordinates& COORDINATES) const;
	const bool areEastSlotsContainWinState(const Coordinates& COORDINATES) const;

	// SOUTH:
	const bool isPossibleToCheckSouthSlots(const Coordinates& COORDINATES) const;
	const bool areSouthSlotsNotEmpty(const Coordinates& COORDINATES) const;
	const bool areSouthSlotsContainWinState(const Coordinates& COORDINATES) const;

	// EAST-SOUTH
	const bool areEastSouthSlotsNotEmpty(const Coordinates& COORDINATES) const;
	const bool areEastSouthSlotsContainWinState(const Coordinates& COORDINATES) const;

	// WEST-SOUTH:
	const bool isPossibleToCheckWestSlots(const Coordinates& COORDINATES) const;
	const bool areWestSouthSlotsNotEmpty(const Coordinates& COORDINATES) const;
	const bool areWestSouthSlotsContainWinState(const Coordinates& COORDINATES) const;
};

#endif