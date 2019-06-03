#include "pch.h"
#include "GameManager.hpp"

const std::string GameManager::EIGHT_SPACE_BARS = "        ";

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::run()
{
	std::cout << "Welcome in game Tic Tac Toe!\n";
	std::cout << "You are facing unconquerable oponent, which use Min-Max algorithm + Alpha & Beta pruning + Dynamic depth limiting in game-tree searching, to calculate next move.\n";
	std::cout << "You can try as much as you wish, but the best what you can get is a draw.\n";
	std::cout << "I would wish you good luck, but it is not going to help any way.\n";

	MainMenuDecision mainMenuDecision;
	OptionMenuDecision optionsMenuDecision;
	do
	{
		printMainMenu();
		mainMenuDecision = getMainMenuDecision(MyStdIn::readNextIntFromValidScope(1, 3));
		switch (mainMenuDecision)
		{
		case PLAY:
			gameLoop();
			break;

		case OPTIONS:
			do
			{
				printOptionsMenu();
				optionsMenuDecision = getOptionMenuDecision(MyStdIn::readNextIntFromValidScope(1, 5));
				executeOptionsDecision(optionsMenuDecision);
			} while (optionsMenuDecision != EXIT_OPTIONS);
			break;

		case EXIT:
			std::cout << "Bye bye !\nThank you for playing my game, psobow!\n";
			break;

		default:
			break;
		}
	} while (mainMenuDecision != EXIT);
}


void GameManager::printMainMenu() const
{
	std::cout << "\nMAIN MENU:\n";
	std::cout << "1.Play\n";
	std::cout << "2.Options\n";
	std::cout << "3.Exit\n";
	std::cout << "Enter choice: ";
}

GameManager::MainMenuDecision GameManager::getMainMenuDecision(const int DECISION_INDEX) const
{
	if (DECISION_INDEX < this->MAIN_MENU_FIRST_OPTION_INDEX || DECISION_INDEX > this->MAIN_MENU_LAST_OPTION_INDEX)
	{
		throw std::invalid_argument("Invalid index for main menu decision.\n");
	}
	return static_cast<GameManager::MainMenuDecision> (DECISION_INDEX);
}


GameManager::OptionMenuDecision GameManager::getOptionMenuDecision(const int DECISION_INDEX) const
{
	if (DECISION_INDEX < this->OPTION_MENU_FIRST_INDEX || DECISION_INDEX > this->OPTION_MENU_LAST_INDEX)
	{
		throw std::invalid_argument("Invalid index for option menu decision.\n");
	}
	return static_cast<GameManager::OptionMenuDecision> (DECISION_INDEX);
}

void GameManager::gameLoop()
{
	bool decision;
	do
	{
		Participant winner = playGame();
		boardManager->resetEverySlot();
		printCheers(winner);
		decision = askAndReadToPlayAgain();
	} while (decision == true);
}

Participant GameManager::playGame()
{
	Coordinates decision(0, 0);
	Participant winner;
	boardManager->printBoard();

	if (gameOptionsManager->getGameStartingPlayer() == Participant::COMPUTER)
	{
		std::cout << "\nComputer move:\n";
		minMaxManager->executeTheBestComputerMove();
		boardManager->printBoard();
	}

	while (true)
	{
		std::cout << "(Playing as: [" << gameOptionsManager->getCharAssignedTo(Participant::HUMAN)
			<< "], Points for win: [" << gameOptionsManager->getPointsRequiredForVictory()
			<< "]) Your turn: \n";

		decision = askAndReadValidHumanCoordinatesDecision();

		boardManager->addNewCharacter(decision, Participant::HUMAN);

		boardManager->printBoard();

		winner = boardManager->findWinner();
		if (boardManager->isAnyEmptySlot() == false || winner != Participant::NONE)
		{
			return winner;
		}

		std::cout << "\nComputer move:\n";

		minMaxManager->executeTheBestComputerMove();

		boardManager->printBoard();

		winner = boardManager->findWinner();
		if (boardManager->isAnyEmptySlot() == false || winner != Participant::NONE)
		{
			return winner;
		}
	}
}

Coordinates GameManager::askAndReadValidHumanCoordinatesDecision() const
{
	int lastValidIndex = gameOptionsManager->getBoardSize() - 1;
	int row = 0, column = 0;
	bool isValid = false;

	do
	{
		std::cout << "Enter ROW: ";
		row = MyStdIn::readNextIntFromValidScope(0, lastValidIndex);

		std::cout << "Enter COLUMN: ";
		column = MyStdIn::readNextIntFromValidScope(0, lastValidIndex);

		if (boardManager->isSlotEmpty(Coordinates(row, column)))
		{
			isValid = true;
		}
		else
		{
			isValid = false;
			std::cerr << "ERROR. Choosen cordinates are already taken!\n";
			std::cerr << "Enter again: \n";
		}
	} while (isValid == false);

	return Coordinates(row, column);
}

bool GameManager::askAndReadToPlayAgain() const
{
	std::vector<char> validChars{ 'Y', 'y', 'N', 'n' };
	std::cout << "Do you want to play again? Y/y = Yes or N/n = No\nEnter choice: ";
	char enteredChar = MyStdIn::readNextCharWithValidation(validChars);

	return (enteredChar == 'Y' || enteredChar == 'y') ? true : false;
}

void GameManager::printCheers(const Participant& winner) const
{
	switch (winner)
	{
	case Participant::HUMAN:
		std::cout << "Magnificent accomplishment! How did you do that ?! Wanna try again ? \n";
		break;

	case Participant::NONE:
		std::cout << "Excelent! You managed to draw!\n";
		break;

	case Participant::COMPUTER:
		std::cout << "Eazy game for computer.\n";
		break;

	default:
		break;
	}
}

void GameManager::printOptionsMenu() const
{
	std::string gameStartingplayer = "";
	(gameOptionsManager->getGameStartingPlayer() == Participant::HUMAN) ? gameStartingplayer = "HUMAN" : gameStartingplayer = "COMPUTER";

	std::cout << "\n" << EIGHT_SPACE_BARS << "OPTIONS MENU:\n";
	std::cout << EIGHT_SPACE_BARS << "1. Switch players symbols ( Current setting: Human ["
		<< gameOptionsManager->getCharAssignedTo(Participant::HUMAN) << "] Computer ["
		<< gameOptionsManager->getCharAssignedTo(Participant::COMPUTER) << "] )\n";

	std::cout << EIGHT_SPACE_BARS << "2. Switch game starting player ( Current player: " << gameStartingplayer << " )\n";
	std::cout << EIGHT_SPACE_BARS << "3. Set new board size ( Current size: " << gameOptionsManager->getBoardSize() << " )\n";
	std::cout << EIGHT_SPACE_BARS << "4. Set points required for victory ( Current points: " << gameOptionsManager->getPointsRequiredForVictory() << " )\n";
	std::cout << EIGHT_SPACE_BARS << "5. Exit options\n";
	std::cout << EIGHT_SPACE_BARS << "Enter choice: ";
}

void GameManager::executeOptionsDecision(const GameManager::OptionMenuDecision& DECISION)
{
	const int MIN_BOARD_SIZE = gameOptionsManager->getMinBoardSize();
	const int MAX_BOARD_SIZE = gameOptionsManager->getMaxBoardSize();

	const int MIN_POINTS_FOR_VICTORY = gameOptionsManager->getMinPointsForVictory();
	const int MAX_POINTS_FOR_VICTORY = gameOptionsManager->getBoardSize();

	switch (DECISION)
	{
	case SWITCH_SYMBOLS:
		gameOptionsManager->switchHumanAndComputerChar();
		break;

	case SWITCH_STARTING_PLAYER:
		gameOptionsManager->setGameStartingPlayer(
			gameOptionsManager->getOppositePlayer(
				gameOptionsManager->getGameStartingPlayer()
			)
		);
		break;

	case SET_BOARD_SIZE:
		std::cout << "\n" << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS
			<< "Minimal board size: " << MIN_BOARD_SIZE
			<< " maximum board size: " << MAX_BOARD_SIZE << "\n";
		std::cout << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS << "Enter choice: ";
		boardManager->resetEverySlotAndSetSize(MyStdIn::readNextIntFromValidScope(MIN_BOARD_SIZE, MAX_BOARD_SIZE));
		break;

	case SET_POINTS_FOR_VICTORY:
		std::cout << "\n" << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS
			<< "Minimal amount of points: " << MIN_POINTS_FOR_VICTORY
			<< " maximum amount of points: " << MAX_POINTS_FOR_VICTORY << "\n";
		std::cout << EIGHT_SPACE_BARS << EIGHT_SPACE_BARS << "Enter choice: ";
		gameOptionsManager->setPointsRequiredForVictory(
			MyStdIn::readNextIntFromValidScope(MIN_POINTS_FOR_VICTORY, MAX_POINTS_FOR_VICTORY));
		break;

	case EXIT_OPTIONS:
		break;

	default:
		break;
	}
}