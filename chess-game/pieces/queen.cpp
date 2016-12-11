#include "queen.h"

#define min(a,b) (a<b ? a : b)

Queen::Queen(Color color)
    :Piece(color,ptQueen)
{
}

std::vector<Coordinate> Queen::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> result;
    int sRow;
    int sColumn;

    // LeftTop to RightBottom diagonal
    sRow = currentPosition.getRow() - min(currentPosition.getRow(),currentPosition.getColumn());
    sColumn = currentPosition.getColumn() - min(currentPosition.getRow(),currentPosition.getColumn());
    while(sRow<8 && sColumn<8) {
        if(sRow!=currentPosition.getRow() || sColumn!=currentPosition.getColumn())
            result.push_back(Coordinate(sRow,sColumn));

        sRow++;
        sColumn++;
    }

    // LeftBottom to RightTop diagonal
    sRow = currentPosition.getRow() + min(7-currentPosition.getRow(),currentPosition.getColumn());
    sColumn = currentPosition.getColumn() - min(7-currentPosition.getRow(),currentPosition.getColumn());
    while(sRow>=0 && sColumn<8) {
        if(sRow!=currentPosition.getRow() || sColumn!=currentPosition.getColumn())
            result.push_back(Coordinate(sRow,sColumn));

        sRow--;
        sColumn++;
    }

    // same row and same column
    for(int i=0;i<8;i++) {
        if(currentPosition.getRow()!=i)
            result.push_back(Coordinate(i,currentPosition.getColumn()));
        if(currentPosition.getColumn()!=i)
            result.push_back(Coordinate(currentPosition.getRow(),i));
    }

    return result;
}

Piece* Queen::getCopy() const
{
    return new Queen(color);
}
