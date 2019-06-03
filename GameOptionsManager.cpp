#include "pch.h"
#include "GameOptionsManager.hpp"

GameOptionsManager* GameOptionsManager::instance = nullptr;

GameOptionsManager* GameOptionsManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameOptionsManager();
	}
	return instance;
}

void GameOptionsManager::setGameStartingPlayer(const GameParticipant& PLAYER)
{
	gameStartingPlayer = PLAYER;

}

void GameOptionsManager::switchHumanAndComputerChar()
{
	char tempHumanChar = humanChar;
	humanChar = computerChar;
	computerChar = tempHumanChar;
}

void GameOptionsManager::setPointsRequiredForVictory(const int NEW_POINTS)										//ustawianie iloœci znaków wymaganych do zwyciêstwa z obs³ug¹ b³êdów z bib. except
{
	if (NEW_POINTS < MIN_POINTS_FOR_VICTORY || NEW_POINTS > boardSize)
	{
		std::string exceptionMessage = "Invalid new amount of points required for victory. Recived argument = "
			+ std::to_string(NEW_POINTS) + "\n";
		throw std::invalid_argument(exceptionMessage);
	}
	pointsRequiredForVictory = NEW_POINTS;
}

void GameOptionsManager::setBoardSize(const int NEW_BOARD_SIZE)													//ustawianie wielkosci planszy i obs³uga b³êdów
{
	if (NEW_BOARD_SIZE < MIN_BOARD_SIZE || NEW_BOARD_SIZE > MAX_BOARD_SIZE)
	{
		std::string exceptionMessage = "Invalid new board size. Recived argument = " + std::to_string(NEW_BOARD_SIZE) + "\n";
		throw std::invalid_argument(exceptionMessage);
	}
	boardSize = NEW_BOARD_SIZE;
}

const Participant GameOptionsManager::getEnumAssignedTo(const char CHAR) const
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

const char GameOptionsManager::getCharAssignedTo(const Participant& PLAYER) const
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

const int GameOptionsManager::getDepthBound(const int BOARD_SIZE) const
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

const Participant GameOptionsManager::getGameStartingPlayer() const
{
	return gameStartingPlayer;
}

const Participant GameOptionsManager::getOppositePlayer(const Participant& PLAYER) const
{
	return static_cast<Participant>(PLAYER*(-1));
}

const int GameOptionsManager::getPointsRequiredForVictory() const
{
	return pointsRequiredForVictory;
}
const int GameOptionsManager::getBoardSize() const
{
	return boardSize;
}

const int GameOptionsManager::getMinBoardSize() const
{
	return MIN_BOARD_SIZE;
}

const int GameOptionsManager::getMinPointsForVictory() const
{
	return MIN_POINTS_FOR_VICTORY;
}

const int GameOptionsManager::getMaxBoardSize() const
{
	return MAX_BOARD_SIZE;
}