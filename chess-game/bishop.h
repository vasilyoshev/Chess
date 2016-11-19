#ifndef BISHOP_H
#define BISHOP_H

#include <QtGlobal>

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
};

#endif // BISHOP_H
