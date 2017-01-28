#include "cellbutton.h"

CellButton::CellButton()
    :QPushButton() {

}

void CellButton::setCoordinate(Coordinate coordinate) {
    this->coordinate = coordinate;
}

Coordinate CellButton::getCoordinate() const {
    return coordinate;
}

void CellButton::setPieceType(Piece::PieceType pieceType)
{
    this->pieceType = pieceType;
}

Piece::PieceType CellButton::getPieceType() const
{
    return pieceType;
}
