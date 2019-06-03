#include "pch.h"
#include "Coordinates.hpp"


Coordinates::Coordinates(const int ROW, const int COL)
{
	if (ROW < 0 || COL < 0 || ROW >= gameOptionsManager->getBoardSize() || COL >= gameOptionsManager->getBoardSize())
	{
		throw std::invalid_argument("Invalid coordinates. Tried to create object with ROW: "
			+ std::to_string(ROW) + " and COL: " + std::to_string(COL) + "\n");
	}
	row = ROW;
	column = COL;
}

const int Coordinates::getRow() const
{
	return row;
}

const int Coordinates::getColumn() const
{
	return column;
}

const bool Coordinates::equals(const Coordinates& COORDINATES) const
{
	return (row == COORDINATES.getRow() && column == COORDINATES.getColumn());
}

void Coordinates::operator = (const Coordinates& COORDINATES)
{
	row = COORDINATES.getRow();
	column = COORDINATES.getColumn();
}