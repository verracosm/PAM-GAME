

#include "pch.h"
#include <iostream>
#include "GameManager.hpp"

int main()
{
	GameManager *gameManager = GameManager::getInstance();
	gameManager->run();
	return 0;
}

