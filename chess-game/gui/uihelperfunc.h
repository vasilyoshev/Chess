#ifndef UIHELPERFUNC_H
#define UIHELPERFUNC_H

#include <QString>
#include "piece.h"
#include "coordinate.h"

/**
 * @brief The UIHelperFunc class
 *
 * This class is used as a namepace to store helper functions that the UI can use in order to visualize
 * appropriate and consistent data.
 */
class UIHelperFunc {
public:
    UIHelperFunc();

    static QString getPieceFileName(Piece *p);
    static QString getFormBackgroundStyleSheet();
    static QString getBackgroundStyleSheet(QString color);
    static QString getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor);

};

#endif // UIHELPERFUNC_H
