#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

#include "coordinate.h"

class CellButton : public QPushButton {
private:
    Coordinate coordinate;
    void (*hoverEnterEvent)();
    void (*hoverLeaveEvent)();

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

public:
    CellButton();

    void setCoordinate(Coordinate coordinate);
    Coordinate getCoordinate() const;
//    void setHoverEvents(void (*hoverEnterEvent)(),void (*hoverLeaveEvent)());
};

#endif // CELLBUTTON_H
