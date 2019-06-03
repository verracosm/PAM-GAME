#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>

#include "Coordinates.hpp"
#include "GameOptionsManager.hpp"

class BoardManager
{
	friend class BoardManagerTestSuite;
public:
	static BoardManager* getInstance();
	~BoardManager() {};

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

	GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();

	// Singleton
	static BoardManager *instance;
	BoardManager();
	BoardManager(const BoardManager&) = delete;
	BoardManager& operator=(const BoardManager&) = delete;


	// TODO: implement algorithm with multi threads.
#pragma region findWinner algorithm
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
#pragma endregion
};

#endif