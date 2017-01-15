#include "queen.h"

#define min(a,b) (a<b ? a : b)

Queen::Queen(Color color)
    :Piece(color,ptQueen) {
}

std::vector< std::vector<Coordinate> > Queen::getPossibleMoves(Coordinate currentPosition) {
    std::vector< std::vector<Coordinate> > result;
    std::vector<Coordinate> upLeft;
    std::vector<Coordinate> upRight;
    std::vector<Coordinate> downLeft;
    std::vector<Coordinate> downRight;
    std::vector<Coordinate> up;
    std::vector<Coordinate> down;
    std::vector<Coordinate> left;
    std::vector<Coordinate> right;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

    //Down right diagonal
    for (int j = col + 1, i = row + 1; j < 8 && i < 8; j++, i++) {
        downRight.push_back(Coordinate(i, j));
    }

    // Up right diagonal
    for (int j = col - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
        upRight.push_back(Coordinate(i, j));
    }

    //Up left diagonal
    for (int j = col - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
        upLeft.push_back(Coordinate(i, j));
    }

    //Down left diagonal
    for (int j = col + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
        downLeft.push_back(Coordinate(i, j));
    }

    //moves up
    for (int i = row - 1; i > -1; i--) {
        up.push_back(Coordinate(i, col));
    }

    //moves down
    for (int i = row + 1; i < 8; i++) {
        down.push_back(Coordinate(i, col));
    }

    //moves right
    for (int i = col + 1; i < 8; i++) {
        right.push_back(Coordinate(row, i));
    }

    //moes left
    for (int i = col - 1; i > -1; i--) {
        left.push_back(Coordinate(row, i));
    }

    result.push_back(up);
    result.push_back(down);
    result.push_back(right);
    result.push_back(left);
    result.push_back(upLeft);
    result.push_back(upRight);
    result.push_back(downLeft);
    result.push_back(downRight);

return result;
    /*
    std::vector<Coordinate> result;
    int sRow;
    int sColumn;

    // LeftTop to RightBottom diagonal
    sRow = currentPosition.getRow() - min(currentPosition.getRow(), currentPosition.getColumn());
    sColumn = currentPosition.getColumn() - min(currentPosition.getRow(),   currentPosition.getColumn());
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

    // same row and same column
    for(int i = 0; i < 8; i++) {
        if(currentPosition.getRow()!= i) {
            result.push_back(Coordinate(i, currentPosition.getColumn()));
        }
        if(currentPosition.getColumn()!= i) {
            result.push_back(Coordinate(currentPosition.getRow(), i));
        }
    }

    return result;
*/
}

Piece* Queen::getCopy() const {
    return new Queen(color);
}
