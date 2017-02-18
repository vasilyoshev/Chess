#ifndef BISHOP_H
#define BISHOP_H

#include <QtGlobal>

#include "piece.h"

/**
 * @brief The Bishop class provides all possible moves for bishop pieces.
 */
class Bishop : public Piece {
public:
    Bishop(Color color);
    std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition);
    Piece* getCopy() const;
};

#endif // BISHOP_H
