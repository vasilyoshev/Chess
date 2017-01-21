#include "rook.h"
#include "piece.h"

Rook::Rook(Color color)
    :Piece(color,ptRook)
{
}

std::vector< std::vector<Coordinate> > Rook::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> up;
    std::vector<Coordinate> down;
    std::vector<Coordinate> left;
    std::vector<Coordinate> right;

    int row = currentPosition.getRow();
    int col = currentPosition.getColumn();

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

    //mvoes left
    for (int i = col - 1; i > -1; i--) {
        left.push_back(Coordinate(row, i));
    }

    std::vector< std::vector<Coordinate> > result;
    result.push_back(up);
    result.push_back(down);
    result.push_back(right);
    result.push_back(left);
    return result;
}

Piece* Rook::getCopy() const {
    return new Rook(color);
}
