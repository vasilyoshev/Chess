#ifndef KING_H
#define KING_H

#include "piece.h"

/**
 * @brief The King class provides all possible moves for king pieces.
 */
class King : public Piece {
public:
    King(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // KING_H
