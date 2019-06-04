#include "pch.h"
#include "Board.hpp"

Board* Board::instance = nullptr;

Board* Board::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Board();
	}
	return instance;
}

Board::Board()
{
	resetEverySlotAndSetSize(gameOptionsManager->getBoardSize());
}

void Board::resetEverySlotAndSetSize(const int NEW_BOARD_SIZE)
{
	// Try to set up new size
	gameOptionsManager->setBoardSize(NEW_BOARD_SIZE);

	// Cleaning
	board.clear();
	quantityOfTakenSlots = 0;

	// Fill up board with empty slot chars
	std::vector<char> row;
	for (int i = 0; i < NEW_BOARD_SIZE; i++)
	{
		row.push_back(gameOptionsManager->getCharAssignedTo(Participant::NONE));
	}
	for (int i = 0; i < NEW_BOARD_SIZE; i++)
	{
		board.push_back(row);
	}
}

void Board::resetEverySlot()
{
	resetEverySlotAndSetSize(gameOptionsManager->getBoardSize());
}

void Board::resetSlot(const Coordinates& COORDINATES)
{
	const bool IS_VALID = (isSlotEmpty(COORDINATES) == false);
	if (IS_VALID)
	{
		board[COORDINATES.getRow()][COORDINATES.getColumn()] = gameOptionsManager->getCharAssignedTo(Participant::NONE);
		quantityOfTakenSlots--;
	}
}

const bool Board::addNewCharacter(const Coordinates& COORDINATES, const Participant& PLAYER)
{
	if (PLAYER != Participant::HUMAN && PLAYER != Participant::COMPUTER)
	{
		throw std::invalid_argument("Invalid player.\n");
	}

	const bool IS_VALID = (isSlotEmpty(COORDINATES));
	if (IS_VALID)
	{
		const char NEW_CHARACTER = gameOptionsManager->getCharAssignedTo(PLAYER);
		board[COORDINATES.getRow()][COORDINATES.getColumn()] = NEW_CHARACTER;
		quantityOfTakenSlots++;
		return true;
	}
	return false;
}

const bool Board::isSlotEmpty(const Coordinates& COORDINATES) const
{
	return (board[COORDINATES.getRow()][COORDINATES.getColumn()] == gameOptionsManager->getCharAssignedTo(Participant::NONE));
}

const bool Board::isAnyEmptySlot() const
{
	return quantityOfTakenSlots < gameOptionsManager->getBoardSize() * gameOptionsManager->getBoardSize();
}

const int Board::getQuantityOfTakenSlots() const
{
	return quantityOfTakenSlots;
}

std::vector<Coordinates> Board::getEveryEmptySlotCoordinates() const
{
	std::vector<Coordinates> emptySlots;
	const int BOARD_SIZE = gameOptionsManager->getBoardSize();

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (isSlotEmpty(Coordinates(row, col)))
			{
				emptySlots.push_back(Coordinates(row, col));
			}
		}
	}
	return emptySlots;
}

void Board::printBoard() const
{
	const int BOARD_SIZE = gameOptionsManager->getBoardSize();
	// print index on the top
	std::cout << "  ";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;

	// print top line 
	std::cout << " +";
	for (int i = 0; i < (2 * BOARD_SIZE) + 1; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;

	// print middle of the board
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		std::cout << row << "|";
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			std::cout << " " << board[row][col];
		}
		std::cout << " |" << std::endl;
	}

	// print bottom line 
	std::cout << " +";
	for (int i = 0; i < (2 * BOARD_SIZE) + 1; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}

//find winner algorithm  

const Participant Board::findWinner() const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int BOARD_SIZE = gameOptionsManager->getBoardSize();

	// there is no winner with this amount of taken slots.
	if (getQuantityOfTakenSlots() < (2 * POINTS_REQUIRED_FOR_VICTORY) - 1) return Participant::NONE;

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			Coordinates currentSlot(row, col);

			if (isSlotEmpty(currentSlot) == false) // Execute algorithm only if slot is taken by one of players
			{
				//EAST:
				const bool EAST_RESULT = isPossibleToCheckEastSlots(currentSlot);
				if (EAST_RESULT)
				{
					if (areEastSlotsNotEmpty(currentSlot))
					{
						if (areEastSlotsContainWinState(currentSlot))
						{
							return gameOptionsManager->getEnumAssignedTo(board[row][col]);
						}
					}
				}

				//SOUTH:
				const bool SOUTH_RESULT = isPossibleToCheckSouthSlots(currentSlot);
				if (SOUTH_RESULT)
				{
					if (areSouthSlotsNotEmpty(currentSlot))
					{
						if (areSouthSlotsContainWinState(currentSlot))
						{
							return gameOptionsManager->getEnumAssignedTo(board[row][col]);
						}
					}
				}

				//EAST-SOUTH:
				if (EAST_RESULT && SOUTH_RESULT)
				{
					if (areEastSouthSlotsNotEmpty(currentSlot))
					{
						if (areEastSouthSlotsContainWinState(currentSlot))
						{
							return gameOptionsManager->getEnumAssignedTo(board[row][col]);
						}
					}
				}

				//WEST-SOUTH:
				const bool WEST_RESULT = isPossibleToCheckWestSlots(currentSlot);
				if (WEST_RESULT && SOUTH_RESULT)
				{
					if (areWestSouthSlotsNotEmpty(currentSlot))
					{
						if (areWestSouthSlotsContainWinState(currentSlot))
						{
							return gameOptionsManager->getEnumAssignedTo(board[row][col]);
						}
					}
				}
			}
		}
	}
	return Participant::NONE;
}

// EAST:

const bool Board::isPossibleToCheckEastSlots(const Coordinates& COORDINATES) const
{
	return (COORDINATES.getColumn() + gameOptionsManager->getPointsRequiredForVictory()<=gameOptionsManager->getBoardSize());
}

const bool Board::areEastSlotsNotEmpty(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();

	for (int col = 1; col < POINTS_REQUIRED_FOR_VICTORY; col++)
	{
		if (isSlotEmpty(Coordinates(ROW, COLUMN + col)) == true)
		{
			return false;
		}
	}
	return true;
}

const bool Board::areEastSlotsContainWinState(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();
	int howManyEqualPairs = 0;

	for (int col = 1; col < POINTS_REQUIRED_FOR_VICTORY; col++)
	{
		if (board[ROW][COLUMN] == board[ROW][COLUMN + col])
		{
			howManyEqualPairs++;
		}
	}
	return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// SOUTH:

const bool Board::isPossibleToCheckSouthSlots(const Coordinates& COORDINATES) const
{
	return (COORDINATES.getRow() + gameOptionsManager->getPointsRequiredForVictory()
		<=
		gameOptionsManager->getBoardSize());
}

const bool Board::areSouthSlotsNotEmpty(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();

	for (int row = 1; row < POINTS_REQUIRED_FOR_VICTORY; row++)
	{
		if (isSlotEmpty(Coordinates(ROW + row, COLUMN)) == true)
		{
			return false;
		}
	}
	return true;
}

const bool Board::areSouthSlotsContainWinState(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();
	int howManyEqualPairs = 0;

	for (int row = 1; row < POINTS_REQUIRED_FOR_VICTORY; row++)
	{
		if (board[ROW][COLUMN] == board[ROW + row][COLUMN])
		{
			howManyEqualPairs++;
		}
	}
	return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// EAST-SOUTH:

const bool Board::areEastSouthSlotsNotEmpty(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();

	for (int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++)
	{
		if (isSlotEmpty(Coordinates(ROW + i, COLUMN + i)) == true)
		{
			return false;
		}
	}
	return true;
}

const bool Board::areEastSouthSlotsContainWinState(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();

	int howManyEqualPairs = 0;
	for (int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++)
	{
		if (board[ROW][COLUMN] == board[ROW + i][COLUMN + i])
		{
			howManyEqualPairs++;
		}
	}
	return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

// WEST-SOUTH:

const bool Board::isPossibleToCheckWestSlots(const Coordinates& COORDINATES) const
{
	return (COORDINATES.getColumn() - gameOptionsManager->getPointsRequiredForVictory() >= -1
		&&
		COORDINATES.getColumn() < gameOptionsManager->getBoardSize());
}

const bool Board::areWestSouthSlotsNotEmpty(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();

	for (int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++)
	{
		if (isSlotEmpty(Coordinates(ROW + i, COLUMN - i)) == true)
		{
			return false;
		}
	}
	return true;
}

const bool Board::areWestSouthSlotsContainWinState(const Coordinates& COORDINATES) const
{
	const int POINTS_REQUIRED_FOR_VICTORY = gameOptionsManager->getPointsRequiredForVictory();
	const int ROW = COORDINATES.getRow();
	const int COLUMN = COORDINATES.getColumn();
	int howManyEqualPairs = 0;

	for (int i = 1; i < POINTS_REQUIRED_FOR_VICTORY; i++)
	{
		if (board[ROW][COLUMN] == board[ROW + i][COLUMN - i])
		{
			howManyEqualPairs++;
		}
	}
	return howManyEqualPairs == (POINTS_REQUIRED_FOR_VICTORY - 1);
}

