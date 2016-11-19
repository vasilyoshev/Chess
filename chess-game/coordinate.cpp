#include "coordinate.h"

Coordinate::Coordinate()
{
    row=-1;
    column=-1;
}

Coordinate::Coordinate(int row, int column)
{
    this->row = row;
    this->column = column;
}

int Coordinate::getRow() const
{
    return row;
}

int Coordinate::getColumn() const
{
    return column;
}

bool Coordinate::isInBoard() const
{
    return row>=0 && row<8 && column>=0 && column<8;
}

bool Coordinate::operator==(const Coordinate &other)
{
    return other.row == row && other.column == column;
}
