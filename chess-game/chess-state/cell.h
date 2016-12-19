#ifndef CELL_H
#define CELL_H

#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

class Cell {
private:
    Piece* piece;

public:
    Cell();

    void setPiece(Piece* piece);
    Piece* getPiece() const;
};

#endif // CELL_H
