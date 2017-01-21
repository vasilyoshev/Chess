#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
    bool hasMoved;
};

#endif // KING_H
