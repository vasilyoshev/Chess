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

/*void CellButton::setHoverEvents(auto hoverEnterEvent,auto hoverLeaveEvent) {
    this->hoverEnterEvent=hoverEnterEvent;
    this->hoverLeaveEvent=hoverLeaveEvent;
}*/

void CellButton::enterEvent(QEvent *e) {
    //hoverEnterEvent();
    QPushButton::enterEvent(e);
}

void CellButton::leaveEvent(QEvent *e) {
    //hoverLeaveEvent();
    QPushButton::leaveEvent(e);
}
