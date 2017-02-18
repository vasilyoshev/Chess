#include "bishop.h"

#define min(a,b) (a<b ? a : b)
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
    std::vector<Coordinate> upLeft;
    std::vector<Coordinate> upRight;
    std::vector<Coordinate> downLeft;
    std::vector<Coordinate> downRight;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    //lower right diagonal
    for (int j = col + 1, i = row + 1; j < 8 && i < 8; j++, i++) {
        downRight.push_back(Coordinate(i, j));
    }

    //lower left diagonal
    for (int j = col - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
        downLeft.push_back(Coordinate(i, j));
    }

    //upper left diagonal
    for (int j = col - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
        upLeft.push_back(Coordinate(i, j));
    }

    //upper right diagonal
    for (int j = col + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
        upRight.push_back(Coordinate(i, j));
    }

    std::vector< std::vector<Coordinate> > result;

    if (upLeft.size() != 0)
        result.push_back(upLeft);
    if (upRight.size() != 0)
        result.push_back(upRight);
    if (downLeft.size() != 0)
        result.push_back(downLeft);
    if (downRight.size() != 0)
        result.push_back(downRight);

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
