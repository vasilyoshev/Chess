#include "bishop.h"

#define min(a,b) (a<b ? a : b)

Bishop::Bishop(Color color)
    :Piece(color,ptBishop) {

}

std::vector< std::vector<Coordinate> > Bishop::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> upLeft;
    std::vector<Coordinate> upRight;
    std::vector<Coordinate> downLeft;
    std::vector<Coordinate> downRight;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    //down right diagonal
    for (int j = col + 1, i = row + 1; j < 8 && i < 8; j++, i++) {
        downRight.push_back(Coordinate(i, j));
    }

    // down left diagonal
    for (int j = col - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
        downLeft.push_back(Coordinate(i, j));
    }

    //Up left diagonal
    for (int j = col - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
        upLeft.push_back(Coordinate(i, j));
    }

    //up right diagonal
    for (int j = col + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
        upRight.push_back(Coordinate(i, j));
    }

    std::vector< std::vector<Coordinate> > result;
    if (upLeft.size() != 0)
        result.push_back(upLeft);
    if (upRight.size() != 0)
        result.push_back(upRight);
    if (downLeft.size() != 0)
        result.push_back(downLeft);
    if (downRight.size() != 0)
        result.push_back(downRight);

    return result;

/*
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
    */

}

Piece* Bishop::getCopy() const {
    return new Bishop(color);
}
