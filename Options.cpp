#include "pch.h"
#include "Options.hpp"

Options* Options::instance = nullptr;

Options* Options::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Options();
	}
	return instance;
}

void Options::setGameStartingPlayer(const GameParticipant& PLAYER)
{
	gameStartingPlayer = PLAYER;
}

void Options::switchHumanAndComputerChar()
{
	char tempHumanChar = humanChar;
	humanChar = computerChar;
	computerChar = tempHumanChar;
}

void Options::setPointsRequiredForVictory(const int NEW_POINTS)										
{
	if (NEW_POINTS < MIN_POINTS_FOR_VICTORY || NEW_POINTS > boardSize)
	{
		std::string exceptionMessage = "Invalid new amount of points required for victory. Recived argument = "
			+ std::to_string(NEW_POINTS) + "\n";
		throw std::invalid_argument(exceptionMessage);
	}
	pointsRequiredForVictory = NEW_POINTS;
}

void Options::setBoardSize(const int NEW_BOARD_SIZE)													
{
	if (NEW_BOARD_SIZE < MIN_BOARD_SIZE || NEW_BOARD_SIZE > MAX_BOARD_SIZE)
	{
		std::string exceptionMessage = "Invalid new board size. Recived argument = " + std::to_string(NEW_BOARD_SIZE) + "\n";
		throw std::invalid_argument(exceptionMessage);
	}
	boardSize = NEW_BOARD_SIZE;
}

const Participant Options::getEnumAssignedTo(const char CHAR) const
{
	if ((CHAR != EMPTY_SLOT_CHAR) && (CHAR != humanChar) && (CHAR != computerChar))
	{
		std::string exceptionMessage = "Invalid char. There is no Game Participant assigned to " + std::to_string(CHAR) + "\n";
		throw std::invalid_argument(exceptionMessage);
	}

	if (CHAR == humanChar)
	{
		return HUMAN;
	}
	else if (CHAR == computerChar)
	{
		return COMPUTER;
	}
	else
	{
		return NONE;
	}
}

const char Options::getCharAssignedTo(const Participant& PLAYER) const
{
	if (PLAYER == NONE)
	{
		return EMPTY_SLOT_CHAR;
	}
	else if (PLAYER == HUMAN)
	{
		return humanChar;
	}
	else
	{
		return computerChar;
	}
}

const int Options::getDepthBound(const int BOARD_SIZE) const
{
	switch (BOARD_SIZE)
	{
	case 3:
		return DEPTH_BOUND_3x3;

	case 4:
		return DEPTH_BOUND_4x4;

	case 5:
		return DEPTH_BOUND_5x5;

	case 6:
		return DEPTH_BOUND_6x6;

	case 7:
		return DEPTH_BOUND_7x7;

	case 8:
		return DEPTH_BOUND_8x8;

	case 9:
		return DEPTH_BOUND_9x9;

	case 10:
		return DEPTH_BOUND_10x10;

	default:
		break;
	}
	throw std::invalid_argument("Invalid argument. Recived argument = " + std::to_string(BOARD_SIZE) + "\n");
}

const Participant Options::getGameStartingPlayer() const
{
	return gameStartingPlayer;
}

const Participant Options::getOppositePlayer(const Participant& PLAYER) const
{
	return static_cast<Participant>(PLAYER*(-1));
}

const int Options::getPointsRequiredForVictory() const
{
	return pointsRequiredForVictory;
}
const int Options::getBoardSize() const
{
	return boardSize;
}

const int Options::getMinBoardSize() const
{
	return MIN_BOARD_SIZE;
}

const int Options::getMinPointsForVictory() const
{
	return MIN_POINTS_FOR_VICTORY;
}

const int Options::getMaxBoardSize() const
{
	return MAX_BOARD_SIZE;
}