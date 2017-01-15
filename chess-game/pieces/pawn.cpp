#include "pawn.h"

Pawn::Pawn(Color color)
    :Piece(color, ptPawn) {
    has_moved = false;
}

std::vector< std::vector<Coordinate> > Pawn::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> moves;

    if(getColor() == cBlack) {
        moves.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn()));
        if (!has_moved) {
            moves.push_back(Coordinate(currentPosition.getRow() + 2, currentPosition.getColumn()));
        }
    } else {
        moves.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn()));
        if (!has_moved) {
            moves.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn()));
        }
    }
    std::vector< std::vector< Coordinate> > result;
    result.push_back(moves);
    return result;
}

Piece* Pawn::getCopy() const {
    Pawn* copy = new Pawn(color);
    copy->has_moved = this->has_moved;
    return copy;
}
