#include "pch.h"
#include "MinMaxManager.hpp"

MinMaxManager* MinMaxManager::instance = nullptr;

MinMaxManager* MinMaxManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MinMaxManager();
	}
	return instance;
}

void MinMaxManager::executeTheBestComputerMove()
{
	if (boardManager->isAnyEmptySlot() == false) return;

	const int INITIAL_DEPTH = 0;

	// in case computer starting the game, just pick (0,0) slot. this one is the best first move, in my opinion.
	if (boardManager->getQuantityOfTakenSlots() == 0)
	{
		theBestMoveCoordinates = Coordinates(0, 0);
	}
	else
	{
		auto start = std::chrono::steady_clock::now();
		calculateTheBestMoveFor(Participant::COMPUTER, INITIAL_DEPTH, this->LOWEST_SCORE, this->HIGHEST_SCORE);
		auto end = std::chrono::steady_clock::now();

		std::cout << "Elapsed time in seconds : " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " sec\n";
		std::cout << "Number of recursive function calls : " << this->howManyFunctionCalls << "\n";
		this->howManyFunctionCalls = 0;
	}

	boardManager->addNewCharacter(theBestMoveCoordinates, Participant::COMPUTER);
}


const int MinMaxManager::calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int currentDepth, int alpha, int beta)
{
	// Terminating condition
	const int RESULT = scoreGameFromComputerPOV(currentDepth);
	if (RESULT != 0 || (boardManager->isAnyEmptySlot() == false)
		|| currentDepth == gameOptionsManager->getDepthBound(gameOptionsManager->getBoardSize()))
	{
		return RESULT;
	}

	this->howManyFunctionCalls++;
	currentDepth++;
	std::vector<Coordinates> availableCoordinates = boardManager->getEveryEmptySlotCoordinates();
	std::vector<int> scores;
	int currentBestScore;

	// This part execute possible moves and evaluate states of the game in order to calculate the best computer move.
	for (unsigned int i = 0; i < availableCoordinates.size(); i++)
	{
		boardManager->addNewCharacter(availableCoordinates[i], TURN_TAKING_PLAYER);
		const int CURRENT_BOARD_SCORE_FROM_COMPUTER_POV = calculateTheBestMoveFor(
			gameOptionsManager->getOppositePlayer(TURN_TAKING_PLAYER), currentDepth, alpha, beta);

		scores.push_back(CURRENT_BOARD_SCORE_FROM_COMPUTER_POV);
		boardManager->resetSlot(availableCoordinates[i]);

		// Alpha pruning
		if (TURN_TAKING_PLAYER == Participant::COMPUTER)
		{
			currentBestScore = *std::max_element(std::begin(scores), std::end(scores));
			alpha = std::max(currentBestScore, alpha); // Alpha is the best value that the maximizer currently can guarantee at that level.
			if (beta <= alpha)
			{
				break;
			}
			// Beta pruning
		}
		else
		{
			currentBestScore = *std::min_element(std::begin(scores), std::end(scores));
			beta = std::min(currentBestScore, beta); // Beta is the best value that the minimizer currently can guarantee at that level.
			if (beta <= alpha)
			{
				break;
			}
		}
	}

	//This part is decision making part
	if (TURN_TAKING_PLAYER == Participant::COMPUTER)
	{ // Computer is going for highiest score from his POV.
		const int MAX_SCORE_INDEX = getMaxValueIndex(scores);
		if (currentDepth == 1)
		{ // At the final point of this algorithm we want to execute the best move for computer at depth equal 1.
			this->theBestMoveCoordinates = availableCoordinates[MAX_SCORE_INDEX];
		}
		return scores[MAX_SCORE_INDEX];

		// In this algoritm we assume that human is also perfect player and he always choose his the best possible move. 
		// That's huge overestimate cuz humans are dumb idiots mostly.
	}
	else if (TURN_TAKING_PLAYER == Participant::HUMAN)
	{ // Human is going for lowest score from computer POV
		const int MIN_SCORE_INDEX = getMinValueIndex(scores);
		return scores[MIN_SCORE_INDEX];
	}
}

const int MinMaxManager::scoreGameFromComputerPOV(const int DEPTH) const
{
	const Participant WINNER = boardManager->findWinner();

	if (WINNER == Participant::COMPUTER)
	{
		return HIGHEST_SCORE - DEPTH;
	}
	else if (WINNER == Participant::NONE)
	{
		return 0;
	}
	else
	{
		return -HIGHEST_SCORE + DEPTH;
	}
}

const int MinMaxManager::getMaxValueIndex(const std::vector<int>& VEC) const
{
	if (VEC.size() == 0)
	{
		throw std::invalid_argument("Invalid argument, vector size equals zero.\n");
	}

	int result = 0;
	int maxValue = VEC[0];
	for (unsigned int i = 1; i < VEC.size(); i++)
	{
		if (VEC[i] > maxValue)
		{
			maxValue = VEC[i];
			result = i;
		}
	}
	return result;
}

const int MinMaxManager::getMinValueIndex(const std::vector<int>& VEC) const
{
	if (VEC.size() == 0)
	{
		throw std::invalid_argument("Invalid argument, vector size equals zero.\n");
	}

	int result = 0;
	int minValue = VEC[0];
	for (unsigned int i = 1; i < VEC.size(); i++)
	{
		if (VEC[i] < minValue)
		{
			minValue = VEC[i];
			result = i;
		}
	}
	return result;
}