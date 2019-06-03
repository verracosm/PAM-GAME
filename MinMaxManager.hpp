#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include "BoardManager.hpp"
#include <algorithm> // for function std::max
#include <chrono> // for time measurement

class MinMaxManager
{
	friend class MinMaxManagerTestSuite;
public:
	static MinMaxManager* getInstance();
	~MinMaxManager() {};

	void executeTheBestComputerMove();

private:
	int howManyFunctionCalls = 0;
	const int HIGHEST_SCORE = 1000;
	const int LOWEST_SCORE = -1000;

	Coordinates theBestMoveCoordinates; // this field must be synchronized in multi-thread algorithm

	GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
	BoardManager *boardManager = BoardManager::getInstance();

	// Singleton
	static MinMaxManager *instance;
	MinMaxManager() : theBestMoveCoordinates(0, 0) {}
	MinMaxManager(const MinMaxManager&) = delete;
	MinMaxManager& operator=(const MinMaxManager&) = delete;

	const int calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth, int alpha, int beta);

	const int scoreGameFromComputerPOV(const int DEPTH) const; // POV = Point of view
	const int getMaxValueIndex(const std::vector<int>& VEC) const;
	const int getMinValueIndex(const std::vector<int>& VEC) const;
};

#endif