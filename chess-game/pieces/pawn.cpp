#include "pawn.h"

Pawn::Pawn(Color color)
    :Piece(color, ptPawn) {
}

std::vector< std::vector<Coordinate> > Pawn::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> diagonals;
    std::vector<Coordinate> forward;
    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    if(getColor() == cBlack) {
        if (row < 7)
            forward.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn()));
        if (!hasMoved)
            forward.push_back(Coordinate(currentPosition.getRow() + 2, currentPosition.getColumn()));
        if (col > 0 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn() - 1));
        if (col < 7 && row < 7)
            diagonals.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn() + 1));
    } else {
        if (row < 7)
            forward.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn()));
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
    std::vector<Coordinate>::const_iterator begin = diagonals.begin();
    for (int i = 0; i < diagonals.size(); i++) {
        result.push_back(std::vector<Coordinate>(begin + i, begin + i + 1));
    }

    return result;
}

Piece* Pawn::getCopy() const {
    return new Pawn(color);
}
