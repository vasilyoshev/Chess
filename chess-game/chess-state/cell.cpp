#include "cell.h"

Cell::Cell()
{
    piece = nullptr;
}

void Cell::setPiece(Piece* piece)
{
    this->piece = piece;
}

Piece* Cell::getPiece() const
{
    return piece;
}
