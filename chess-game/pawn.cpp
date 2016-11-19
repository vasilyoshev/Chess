#include "pawn.h"

Pawn::Pawn(Color color)
    :Piece(color,ptPawn)
{
}

std::vector<Coordinate> Pawn::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> result;
    if(getColor()==cBlack) {
        result.push_back(Coordinate(currentPosition.getRow()+1,currentPosition.getColumn()));
    } else {
        result.push_back(Coordinate(currentPosition.getRow()-1,currentPosition.getColumn()));
    }

    return result;
}
