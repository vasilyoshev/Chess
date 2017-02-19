#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

/**
 * @brief The Knight class provides all possible moves for knight pieces.
 */
class Knight : public Piece {
public:
    Knight(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // KNIGHT_H
