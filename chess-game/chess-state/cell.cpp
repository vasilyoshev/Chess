#include "cell.h"

Cell::Cell() {
    piece = nullptr;
}

Cell::Cell(const Cell& cell) {
    if(cell.piece != nullptr) {
        piece = cell.piece->getCopy();
    } else {
        piece = nullptr;
    }
}

void Cell::setPiece(Piece* piece) {
    this->piece = piece;
}

Piece* Cell::getPiece() const {
    return piece;
}
