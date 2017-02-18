#include "pawn.h"

/**
 * @brief Pawn::Pawn
 */
Pawn::Pawn(Color color)
    :Piece(color, ptPawn) {
}

/**
 * @brief Pawn::getPossibleMoves
 *
 * Gets all possible moves for this type of Piece.
 *
 * @param currentPosition - the position for which the possible moves are to be checked.
 * @return vector of vectors, where every vector holds all moves in a given direction.
 */
std::vector< std::vector<Coordinate> > Pawn::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> diagonals;
    std::vector<Coordinate> forward;
    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();
    //add forward and diagonal moves if they not outside the board
    if(getColor() == cBlack) {
        if (row < 7)
            forward.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn()));
        //if pawn hasn't moved also add 2 moves forward
        if (!hasMoved)
            forward.push_back(Coordinate(currentPosition.getRow() + 2, currentPosition.getColumn()));
        if (col > 0 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn() - 1));
        if (col < 7 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn() + 1));
    } else {
        if (row < 7)
            forward.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn()));
        //if pawn hasn't moved also add 2 moves forward
        if (!hasMoved)
            forward.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn()));
        if (col > 0 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn() - 1));
        if (col < 7 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn() + 1));
        }

    std::vector< std::vector< Coordinate> > result;
    if (forward.size() != 0)
        result.push_back(forward);

    //split diagonal moves into separate vectors and add them to result
    std::vector<Coordinate>::const_iterator begin = diagonals.begin();
    for (std::size_t i = 0; i < diagonals.size(); i++) {
        result.push_back(std::vector<Coordinate>(begin + i, begin + i + 1));
    }

    return result;
}

/**
 * @brief Pawn::getCopy
 *
 * Generates a copy for this piece.
 *
 * @return Copy of the piece.
 */
Piece* Pawn::getCopy() const {
    return new Pawn(color);
}
