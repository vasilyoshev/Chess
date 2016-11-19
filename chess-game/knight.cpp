#include "knight.h"

Knight::Knight(Color color)
    :Piece(color,ptKnight)
{
}

std::vector<Coordinate> Knight::getPossibleMoves(Coordinate currentPosition)
{
    std::vector<Coordinate> result;

    result.push_back(Coordinate(currentPosition.getRow()-2,currentPosition.getColumn()-1));
    result.push_back(Coordinate(currentPosition.getRow()-2,currentPosition.getColumn()+1));
    result.push_back(Coordinate(currentPosition.getRow()-1,currentPosition.getColumn()-2));
    result.push_back(Coordinate(currentPosition.getRow()-1,currentPosition.getColumn()+2));
    result.push_back(Coordinate(currentPosition.getRow()+1,currentPosition.getColumn()-2));
    result.push_back(Coordinate(currentPosition.getRow()+1,currentPosition.getColumn()+2));
    result.push_back(Coordinate(currentPosition.getRow()+2,currentPosition.getColumn()-1));
    result.push_back(Coordinate(currentPosition.getRow()+2,currentPosition.getColumn()+1));

    // Remove positions outside the board
    std::vector<Coordinate>::iterator it = result.begin();
    for(;it!=result.end();) {
        if(!it->isInBoard()) {
            it = result.erase(it);
        } else {
            ++it;
        }
    }

    return result;
}
