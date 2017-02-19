#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "coordinate.h"
#include "color.h"

/**
 * @brief The Piece class provides methods and fields common for all pieces.
 */
class Piece {
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
    virtual ~Piece();
    virtual std::vector< std::vector<Coordinate> > getPossibleMoves(Coordinate currentPosition) = 0;
    virtual Piece* getCopy() const = 0;
    Color getColor() const;
    PieceType getType() const;
    void setMoved();
    bool getMoved();

protected:
    Color color;
    PieceType pieceType;
    bool hasMoved;
};

#endif // PIECE_H
