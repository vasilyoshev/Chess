#include "knight.h"

Knight::Knight(Color color)
    :Piece(color,ptKnight) {
}

std::vector< std::vector<Coordinate> > Knight::getPossibleMoves(Coordinate currentPosition) {
    std::vector<Coordinate> moves;
    //get all possible moves
    moves.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn() - 1));
    moves.push_back(Coordinate(currentPosition.getRow() - 2, currentPosition.getColumn() + 1));
    moves.push_back(Coordinate(currentPosition.getRow() - 1, currentPosition.getColumn() - 2));
    moves.push_back(Coordinate(currentPosition.getRow() -1, currentPosition.getColumn() + 2));
    moves.push_back(Coordinate(currentPosition.getRow() +1, currentPosition.getColumn() - 2));
    moves.push_back(Coordinate(currentPosition.getRow() +1, currentPosition.getColumn() + 2));
    moves.push_back(Coordinate(currentPosition.getRow() +2, currentPosition.getColumn() - 1));
    moves.push_back(Coordinate(currentPosition.getRow() +2, currentPosition.getColumn() + 1));

    //remove moves outside the board
    std::vector<Coordinate>::iterator it = moves.begin();
    for(; it != moves.end();) {
        if(!it->isInBoard()) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    std::vector< std::vector<Coordinate> > result;

    //split every move in a separate vector and add it to the result to be returned
    std::vector<Coordinate>::const_iterator begin = moves.begin();
    for (std::size_t i = 0; i < moves.size(); i++) {
        result.push_back(std::vector<Coordinate>(begin + i, begin + i + 1));
    }
    return result;
}

Piece* Knight::getCopy() const {
    return new Knight(color);
}
