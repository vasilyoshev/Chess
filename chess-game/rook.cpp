#include "rook.h"

Rook::Rook(Color color)
    :Piece(color,ptRook)
{
}

std::vector<Coordinate> Rook::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> result;

    for(int i=0;i<8;i++) {
        if(currentPosition.getRow()!=i)
            result.push_back(Coordinate(i,currentPosition.getColumn()));
        if(currentPosition.getColumn()!=i)
            result.push_back(Coordinate(currentPosition.getRow(),i));
    }

    return result;
}

Piece* Rook::getCopy() const
{
    return new Rook(color);
}
