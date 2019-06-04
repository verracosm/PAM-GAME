#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <stdexcept>


class Options
{
public:
	enum GameParticipant
	{
		COMPUTER = -1, NONE = 0, HUMAN = 1
	};

	static Options* getInstance();
	~Options() {};

	void switchHumanAndComputerChar();

	void setPointsRequiredForVictory(const int NEW_POINTS);
	void setBoardSize(const int NEW_BOARD_SIZE);
	void setGameStartingPlayer(const GameParticipant& PLAYER);

	const int getPointsRequiredForVictory() const;
	const int getBoardSize() const;

	const int getMinBoardSize() const;
	const int getMaxBoardSize() const;

	const int getMinPointsForVictory() const;
	const int getMaxPointsForVictory() const;

	const int getDepthBound(const int BOARD_SIZE) const;

	const char getCharAssignedTo(const GameParticipant& PLAYER) const;

	const GameParticipant getEnumAssignedTo(const char CHAR) const;
	const GameParticipant getOppositePlayer(const GameParticipant& PLAYER) const;
	const GameParticipant getGameStartingPlayer() const;

private:
	const char EMPTY_SLOT_CHAR = '-';
	const char DEFAULT_HUMAN_CHAR = 'O';
	const char DEFAULT_COMPUTER_CHAR = 'X';

	const int MIN_BOARD_SIZE = 3;
	const int MAX_BOARD_SIZE = 10;

	const int MIN_POINTS_FOR_VICTORY = 3;

	// These depth boundaries have been picked by trial-and-error method, in order to perform best computing time and efficient decision.
	// 6 is lowest bound which give efficient result for 3 points required to victory
	const int DEPTH_BOUND_3x3 = 9;
	const int DEPTH_BOUND_4x4 = 9;
	const int DEPTH_BOUND_5x5 = 7;
	const int DEPTH_BOUND_6x6 = 6;
	const int DEPTH_BOUND_7x7 = 5;
	const int DEPTH_BOUND_8x8 = 5;
	const int DEPTH_BOUND_9x9 = 4;
	const int DEPTH_BOUND_10x10 = 4;

	GameParticipant gameStartingPlayer = GameParticipant::HUMAN;

	int pointsRequiredForVictory = MIN_POINTS_FOR_VICTORY;
	int boardSize = MIN_BOARD_SIZE;

	char humanChar = DEFAULT_HUMAN_CHAR;
	char computerChar = DEFAULT_COMPUTER_CHAR;

	// Singleton
	static Options *instance;				//pointer
	Options() {};
	Options(const Options&) = delete;
	Options& operator=(const Options&) = delete;
};

typedef Options::GameParticipant Participant;

#endif