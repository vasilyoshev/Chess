#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // QUEEN_H
