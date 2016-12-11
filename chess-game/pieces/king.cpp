#include "king.h"

King::King(Color color)
    : Piece(color,ptKing)
{
}

std::vector<Coordinate> King::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> result;

    for(int col=currentPosition.getColumn()-1;col<=currentPosition.getColumn()+1;col++) {
        for(int row=currentPosition.getRow()-1;row<=currentPosition.getRow()+1;row++) {
            if(col==currentPosition.getColumn() && row==currentPosition.getRow() ||
                    col<0 || col>=8 || row<0 || row>=8)
                continue;

            result.push_back(Coordinate(row,col));
        }
    }

    return result;
}

Piece* King::getCopy() const
{
    return new King(color);
}
