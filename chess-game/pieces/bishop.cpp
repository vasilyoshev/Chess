#include "bishop.h"

#define min(a,b) (a<b ? a : b)

Bishop::Bishop(Color color)
    :Piece(color,ptBishop) {

}

std::vector<Coordinate> Bishop::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> result;
    int sRow;
    int sColumn;

    // LeftTop to RightBottom diagonal
    sRow = currentPosition.getRow() - min(currentPosition.getRow(), currentPosition.getColumn());
    sColumn = currentPosition.getColumn() - min(currentPosition.getRow(), currentPosition.getColumn());
    while(sRow < 8 && sColumn < 8) {
        if(sRow != currentPosition.getRow() || sColumn != currentPosition.getColumn())
            result.push_back(Coordinate(sRow, sColumn));

        sRow++;
        sColumn++;
    }

    // LeftBottom to RightTop diagonal
    sRow = currentPosition.getRow() + min(7 - currentPosition.getRow(), currentPosition.getColumn());
    sColumn = currentPosition.getColumn() - min(7 - currentPosition.getRow(), currentPosition.getColumn());

    while(sRow >= 0 && sColumn < 8) {
        if(sRow != currentPosition.getRow() || sColumn != currentPosition.getColumn())
            result.push_back(Coordinate(sRow, sColumn));

        sRow--;
        sColumn++;
    }

    return result;
}

Piece* Bishop::getCopy() const {
    return new Bishop(color);
}
