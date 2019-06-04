#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <vector>
#include <string>

class Load
{
public:
	const static int readNextInt();
	const static int readNextIntFromValidScope(const int BOTTOM, const int TOP);

	const static char readNextCharWithValidation(const std::vector<char> VALID_CHARS);

private:
	const static bool isVectorContainChar(const std::vector<char> VEC, const char CHARACTER);
};

#endif