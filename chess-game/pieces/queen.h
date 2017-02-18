#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

/**
 * @brief The Queen class provides all possible moves for queen pieces.
 */
class Queen : public Piece {
public:
    Queen(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // QUEEN_H
