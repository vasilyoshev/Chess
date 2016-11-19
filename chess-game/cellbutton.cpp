#include "cellbutton.h"

CellButton::CellButton()
    :QPushButton()
{

}

void CellButton::setCoordinate(Coordinate coordinate)
{
    this->coordinate = coordinate;
}

Coordinate CellButton::getCoordinate() const
{
    return coordinate;
}
