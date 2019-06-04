#include "pch.h"
#include "Load.hpp"


const int Load::readNextInt()
{
	int number = 0;
	std::string inputLine;
	bool isValid;

	do
	{
		isValid = true;
		std::getline(std::cin, inputLine);
		try
		{
			number = std::stoi(inputLine);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			std::cerr << "ERROR. The entered number must be an integer.\n";
			std::cerr << "Enter again: ";
			isValid = false;
		}
	} while (isValid == false);

	return number;
}

const int Load::readNextIntFromValidScope(const int BOTTOM, const int TOP)
{
	int number = 0;
	bool isValid;

	do
	{
		isValid = true;
		number = readNextInt();
		if (number < BOTTOM || number > TOP)
		{
			std::cerr << "ERROR. The entered number must be integer from " << BOTTOM << " to " << TOP << ".\n";
			std::cerr << "Enter again: ";
			isValid = false;
		}

	} while (isValid == false);

	return number;
}

const char Load::readNextCharWithValidation(const std::vector<char> VALID_CHARS)
{
	std::string inputLine;
	bool isValid;

	do
	{
		isValid = true;
		std::getline(std::cin, inputLine);
		if (isVectorContainChar(VALID_CHARS, inputLine[0]) == false)
		{
			std::cerr << "ERROR. The entered character must be one of : [ ";
			for (unsigned int i = 0; i < VALID_CHARS.size(); i++)
			{
				std::cerr << VALID_CHARS[i] << " ";
			}
			std::cerr << "].\n";
			std::cerr << "Enter again: ";
			isValid = false;
		}
	} while (isValid == false);

	return inputLine[0];
}

const bool Load::isVectorContainChar(const std::vector<char> VEC, const char CHARACTER)
{
	for (unsigned int i = 0; i < VEC.size(); i++)
	{
		if (VEC[i] == CHARACTER)
		{
			return true;
		}
	}
	return false;
}