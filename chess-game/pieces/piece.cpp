#include "piece.h"

// Should be interface

/**
 * @brief Piece::Piece
 */
Piece::Piece(Color color, PieceType pieceType) {
    this->color = color;
    this->pieceType = pieceType;
}

/**
 * @brief Piece::~Piece
 */
Piece::~Piece() {
}

/**
 * @brief Piece::isKilled
 *
 * @return true if piece is killed
 */

/**
 * @brief Piece::getColor
 *
 * @return color of the piece
 */
Color Piece::getColor() const {
    return color;
}

/**
 * @brief Piece::getType
 *
 * @return type of the piece
 */
Piece::PieceType Piece::getType() const {
    return pieceType;
}

/**
 * @brief Piece::setMoved
 *
 * @return sets hasMoved of the piece to true
 */
void Piece::setMoved() {
    hasMoved = true;
}

/**
 * @brief Piece::setMoved
 *
 * @return true if piece has moved
 */
bool Piece::getMoved() {
    return hasMoved;
}
