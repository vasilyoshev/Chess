#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
};

#endif // KNIGHT_H
