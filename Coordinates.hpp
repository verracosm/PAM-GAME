#ifndef COORDINATES_H
#define COORDINATES_H

#include "Options.hpp"

class Coordinates
{
public:
	Coordinates(const int ROW, const int COL);

	void operator = (const Coordinates& COORDINATES);

	const bool equals(const Coordinates& COORDINATES) const;

	const int getRow() const;
	const int getColumn() const;

private:

	Options *gameOptionsManager = Options::getInstance();

	int row;
	int column;
};

#endif