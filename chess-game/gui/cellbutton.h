#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

#include "coordinate.h"
#include "piece.h"

/**
 * @brief The CellButton class
 *
 * This class is used to add a single coordinate property to the buttons used on the grid of fields.
 *
 * It inherits the funcionalities of QPushButton and adds only a Coordinate field. It is useful when a particular button is clicked
 * and the UI logic wants to know at which position the button is.
 */
class CellButton : public QPushButton {
private:
    Coordinate coordinate;
    Piece::PieceType pieceType;

public:
    CellButton();

    void setCoordinate(Coordinate coordinate);
    Coordinate getCoordinate() const;
    void setPieceType(Piece::PieceType pieceType);
    Piece::PieceType getPieceType() const;
};

#endif // CELLBUTTON_H
