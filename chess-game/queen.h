#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
};

#endif // QUEEN_H
