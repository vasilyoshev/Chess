#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

#include "coordinate.h"

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

public:
    CellButton();

    void setCoordinate(Coordinate coordinate);
    Coordinate getCoordinate() const;
};

#endif // CELLBUTTON_H
