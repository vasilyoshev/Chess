#include "coordinate.h"

/**
 * @brief Coordinate::Coordinate
 * Default constructor
 */
Coordinate::Coordinate() {
    row =- 1;
    column =- 1;
}

/**
 * @brief Coordinate::Coordinate
 * Parametric constructor
 *
 * @param row the row of the coordinate
 * @param column the column of the coordinate
 */
Coordinate::Coordinate(int row, int column) {
    this->row = row;
    this->column = column;
}

/**
 * @brief Coordinate::getRow
 * Returns the row of the coordinate
 *
 * @return the row of the coordinate
 */
int Coordinate::getRow() const {
    return row;
}

/**
 * @brief Coordinate::getColumn
 * Returns the column of the coordinate
 *
 * @return the column of the coordinate
 */
int Coordinate::getColumn() const {
    return column;
}

/**
 * @brief Coordinate::isInBoard
 * Checks if the given coordinate is in the board
 *
 * @return true if the coordinate is in the board, false otherwise
 */
bool Coordinate::isInBoard() const {
    return (row >= 0 && row < 8 && column >= 0 && column < 8);
}

/**
 * @brief Coordinate::operator ==
 * == operator
 *
 * @param other the other coordinate
 * @return true if the rows and the columns of the two objects are the same
 */
bool Coordinate::operator==(const Coordinate &other) {
    return (other.row == row && other.column == column);
}

/**
 * @brief Coordinate::operator =
 * = operator
 *
 * @param other the coordinate object from which the row and columns sohuld be copied
 */
void Coordinate::operator=(const Coordinate &other) {
    row = other.row;
    column = other.column;
}
