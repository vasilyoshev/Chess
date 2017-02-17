#include "cell.h"

/**
 * @brief Cell::Cell
 *
 * Default constructor sets the piece to nullptr
 */
Cell::Cell() {
    piece = nullptr;
}

/**
 * @brief Cell::Cell
 * Copy constructor
 *
 * @param cell
 */
Cell::Cell(const Cell& cell) {
    if(cell.piece != nullptr) {
        piece = cell.piece->getCopy();
    } else {
        piece = nullptr;
    }
}

/**
 * @brief Cell::setPiece
 * Sets a piece into the cell
 *
 * @param piece the piece to set
 */
void Cell::setPiece(Piece* piece) {
    this->piece = piece;
}

/**
 * @brief Cell::getPiece
 *
 * @return the piece from the cell, nullptr if there isn't one
 */
Piece* Cell::getPiece() const {
    return piece;
}
