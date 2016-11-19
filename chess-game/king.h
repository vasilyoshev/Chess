#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
};

#endif // KING_H
