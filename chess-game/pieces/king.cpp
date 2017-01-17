#include "king.h"

King::King(Color color)
    : Piece(color,ptKing)
{
}

std::vector< std::vector<Coordinate> > King::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> moves;
    for(int col=currentPosition.getColumn()-1;col<=currentPosition.getColumn()+1;col++) {
        for(int row=currentPosition.getRow()-1;row<=currentPosition.getRow()+1;row++) {
            if(col==currentPosition.getColumn() && row==currentPosition.getRow() ||
                    col<0 || col>=8 || row<0 || row>=8)
                continue;

            moves.push_back(Coordinate(row,col));
        }
    }

    std::vector< std::vector<Coordinate> > result;
    std::vector<Coordinate>::const_iterator begin = moves.begin();
    for (int i = 0; i < moves.size(); i++) {
        result.push_back(std::vector<Coordinate>(begin + i, begin + i + 1));
    }
    return result;
}

Piece* King::getCopy() const
{
    return new King(color);
}
