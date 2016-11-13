#ifndef PIECE_H
#define PIECE_H

#include "coordinate.h"
#include "color.h"

class Piece
{
public:
    Piece(Color color);
    //virtual Coordinate[] getPossibleMoves(Coordinate currentPosition)=0;
    virtual bool isKilled() = 0;
    virtual Color getColor() const = 0;
};

#endif // PIECE_H
