#include "piece.h"

// Should be interface

Piece::Piece(Color color,PieceType pieceType)
{
    this->color = color;
    this->pieceType = pieceType;
    killed = false;
}

Piece::~Piece() {

}

bool Piece::isKilled()
{
    return killed;
}

Color Piece::getColor() const
{
    return color;
}

Piece::PieceType Piece::getType() const
{
    return pieceType;
}
