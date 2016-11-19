#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

#include "coordinate.h"

class CellButton : public QPushButton
{
private:
    Coordinate coordinate;
public:
    CellButton();

    void setCoordinate(Coordinate coordinate);
    Coordinate getCoordinate() const;
};

#endif // CELLBUTTON_H
