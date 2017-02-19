#include "bishop.h"

/**
 * @brief Bishop::Bishop
 */
Bishop::Bishop(Color color)
    :Piece(color,ptBishop) {

}

/**
 * @brief Bishop::getPossibleMoves
 *
 * Gets all possible moves for this type of Piece.
 *
 * @param currentPosition - the position for which the possible moves are to be checked.
 * @return vector of vectors, where every vector holds all moves in a given direction.
 */
std::vector< std::vector<Coordinate> > Bishop::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> upperLeft;
    std::vector<Coordinate> upperRight;
    std::vector<Coordinate> lowerLeft;
    std::vector<Coordinate> lowerRight;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    //lower right diagonal
    for (int j = col + 1, i = row + 1; j < 8 && i < 8; j++, i++) {
        lowerRight.push_back(Coordinate(i, j));
    }

    //lower left diagonal
    for (int j = col - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
        lowerLeft.push_back(Coordinate(i, j));
    }

    //upper left diagonal
    for (int j = col - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
        upperLeft.push_back(Coordinate(i, j));
    }

    //upper right diagonal
    for (int j = col + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
        upperRight.push_back(Coordinate(i, j));
    }

    std::vector< std::vector<Coordinate> > result;

    if (upperLeft.size() != 0)
        result.push_back(upperLeft);
    if (upperRight.size() != 0)
        result.push_back(upperRight);
    if (lowerLeft.size() != 0)
        result.push_back(lowerLeft);
    if (lowerRight.size() != 0)
        result.push_back(lowerRight);

    return result;
}

/**
 * @brief Bishop::getCopy
 *
 * Generates a copy for this piece.
 *
 * @return Copy of the piece.
 */
Piece* Bishop::getCopy() const {
    return new Bishop(color);
}
