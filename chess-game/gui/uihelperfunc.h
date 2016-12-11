#ifndef UIHELPERFUNC_H
#define UIHELPERFUNC_H

#include <QString>
#include "piece.h"
#include "coordinate.h"

class UIHelperFunc
{
public:
    UIHelperFunc();

    static QString getPieceFileName(Piece *p);
    static QString getFormBackgroundStyleSheet();
    static QString getBackgroundStyleSheet(QString color);
    static QString getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor);

};

#endif // UIHELPERFUNC_H
