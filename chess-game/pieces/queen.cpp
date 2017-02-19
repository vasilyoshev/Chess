#include "queen.h"

/**
 * @brief Queen::Queen
 */
Queen::Queen(Color color)
    :Piece(color,ptQueen) {
}

/**
 * @brief Queen::getPossibleMoves
 *
 * Gets all possible moves for this type of Piece.
 *
 * @param currentPosition - the position for which the possible moves are to be checked.
 * @return vector of vectors, where every vector holds all moves in a given direction.
 */
std::vector< std::vector<Coordinate> > Queen::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> upperLeft;
    std::vector<Coordinate> upperRight;
    std::vector<Coordinate> lowerLeft;
    std::vector<Coordinate> lowerRight;
    std::vector<Coordinate> up;
    std::vector<Coordinate> down;
    std::vector<Coordinate> left;
    std::vector<Coordinate> right;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    //lower right diagonal
    for (int j = col + 1, i = row + 1; j < 8 && i < 8; j++, i++) {
        lowerRight.push_back(Coordinate(i, j));
    }

    // upper right diagonal
    for (int j = col - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
        upperRight.push_back(Coordinate(i, j));
    }

    //upper left diagonal
    for (int j = col - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
        upperLeft.push_back(Coordinate(i, j));
    }

    //lower left diagonal
    for (int j = col + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
        lowerLeft.push_back(Coordinate(i, j));
    }

    //moves up
    for (int i = row - 1; i > -1; i--) {
        up.push_back(Coordinate(i, col));
    }

    //moves down
    for (int i = row + 1; i < 8; i++) {
        down.push_back(Coordinate(i, col));
    }

    //moves right
    for (int i = col + 1; i < 8; i++) {
        right.push_back(Coordinate(row, i));
    }

    //moves left
    for (int i = col - 1; i > -1; i--) {
        left.push_back(Coordinate(row, i));
    }

    std::vector< std::vector<Coordinate> > result;

    result.push_back(up);
    result.push_back(down);
    result.push_back(right);
    result.push_back(left);
    result.push_back(upperLeft);
    result.push_back(upperRight);
    result.push_back(lowerLeft);
    result.push_back(lowerRight);

    return result;
}

/**
 * @brief Queen::getCopy
 *
 * Generates a copy for this piece.
 *
 * @return Copy of the piece.
 */
Piece* Queen::getCopy() const {
    return new Queen(color);
}
