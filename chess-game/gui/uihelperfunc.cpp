#include "uihelperfunc.h"

UIHelperFunc::UIHelperFunc() {

}

/**
 * @brief UIHelperFunc::getPieceFileName
 * @param p Object of subtype of Piece.
 * @return Returns the filename of the type of the piece.
 *
 * Given an object of a subclass of a piece, this method returns the filename that should be looked for in the directory with images.
 */
QString UIHelperFunc::getPieceFileName(Piece *p) {
    if(p==nullptr) {
        return "";
    }

    QString result;
    switch(p->getType()) {
    case Piece::ptKing :
        result="Dama";
        break;
    case Piece::ptQueen :
        result="Car";
        break;
    case Piece::ptRook :
        result="Top";
        break;
    case Piece::ptBishop :
        result="Oficer";
        break;
    case Piece::ptKnight :
        result="Kon";
        break;
    case Piece::ptPawn :
        result="Peshka";
        break;
    }

    if(p->getColor()==cBlack) {
        result += "B";
    } else {
        result += "W";
    }

    return result;
}

/**
 * @brief UIHelperFunc::getFormBackgroundStyleSheet
 * @return Returns a stylesheet format of the background of the windows that are visualized.
 */
QString UIHelperFunc::getFormBackgroundStyleSheet() {
    return "background-color : rgb(220,200,140,100%);";
}

/**
 * @brief UIHelperFunc::getBackgroundStyleSheet
 * @param color A color of the field.
 * @return Returns a stylesheet format of a field in the board.
 */
QString UIHelperFunc::getBackgroundStyleSheet(QString color) {
    return QString("QPushButton { background-color : ")+ color + "; border: 1px solid black;}";
}

/**
 * @brief UIHelperFunc::getBackgroundAndHoverStyleSheet
 * @param backgroundColor Color of the background without hover event.
 * @param hoverColor Color of the background with hover event.
 * @return Returns a stylesheet format of a field in the board which has a hover event.
 */
QString UIHelperFunc::getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor) {
    return QString("QPushButton {background-color: "+backgroundColor+"} ")
            +"QPushButton:hover {background-color: "+hoverColor+";}";
}
