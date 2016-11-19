#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "coordinate.h"
#include "color.h"

class Piece
{
private:
    Color color;
public:

    enum PieceType {
        ptKing,
        ptQueen,
        ptRook,
        ptBishop,
        ptKnight,
        ptPawn
    };

    Piece(Color color,PieceType pieceType);
    virtual std::vector<Coordinate> getPossibleMoves(Coordinate currentPosition)=0;
    bool isKilled();
    Color getColor() const;
    PieceType getType() const;

protected:
    bool killed;
    PieceType pieceType;
};

#endif // PIECE_H
