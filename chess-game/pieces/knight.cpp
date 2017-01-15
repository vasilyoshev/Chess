#include "knight.h"

Knight::Knight(Color color)
    :Piece(color,ptKnight) {
}

std::vector< std::vector<Coordinate> > Knight::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> moves;

    moves.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn() - 1));
    moves.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn() + 1));
    moves.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn() - 2));
    moves.push_back(Coordinate(currentPosition.getRow() -1, currentPosition.getColumn() + 2));
    moves.push_back(Coordinate(currentPosition.getRow() +1, currentPosition.getColumn() - 2));
    moves.push_back(Coordinate(currentPosition.getRow() +1, currentPosition.getColumn() + 2));
    moves.push_back(Coordinate(currentPosition.getRow() +2, currentPosition.getColumn() - 1));
    moves.push_back(Coordinate(currentPosition.getRow() +2, currentPosition.getColumn() + 1));

    // Remove positions outside the board
    std::vector<Coordinate>::iterator it = moves.begin();
    for(; it != moves.end();) {
        if(!it->isInBoard()) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    std::vector< std::vector<Coordinate> > result;
    result.push_back(moves);
    return result;
}

Piece* Knight::getCopy() const {
    return new Knight(color);
}
