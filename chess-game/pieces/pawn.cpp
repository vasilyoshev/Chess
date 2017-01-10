#include "pawn.h"

Pawn::Pawn(Color color)
    :Piece(color,ptPawn) {
    has_moved = false;
}

std::vector<Coordinate> Pawn::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> result;

    if(getColor() == cBlack) {
        if (has_moved) {
            result.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn()));
        } else {
            result.push_back(Coordinate(currentPosition.getRow() + 2, currentPosition.getColumn()));
            result.push_back(Coordinate(currentPosition.getRow() + 1, currentPosition.getColumn()));
            has_moved = true;
        }
    } else {
        if (has_moved) {
            result.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn()));
        } else {
            result.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn()));
            result.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn()));
            has_moved = true;
        }
    }

    return result;
}

Piece* Pawn::getCopy() const {
    return new Pawn(color);
}
