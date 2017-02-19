#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

/**
 * @brief The Pawn class provides all possible moves for pawn pieces.
 */
class Pawn : public Piece {

public:
    Pawn(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // PAWN_H
