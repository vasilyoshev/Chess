#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(Color color);
    std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // PAWN_H
