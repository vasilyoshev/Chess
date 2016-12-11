#include "uihelperfunc.h"

UIHelperFunc::UIHelperFunc()
{

}

QString UIHelperFunc::getPieceFileName(Piece *p)
{
    if(p==nullptr)
        return "";

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

QString UIHelperFunc::getFormBackgroundStyleSheet()
{
    return "background-color : rgb(220,200,140,100%);";
}

QString UIHelperFunc::getBackgroundStyleSheet(QString color)
{
    return QString("QPushButton { background-color : ")+ color + "; border: 1px solid black;}";
}

QString UIHelperFunc::getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor)
{
    return QString("QPushButton {background-color: "+backgroundColor+"} ")
            +"QPushButton:hover {background-color: "+hoverColor+";}";
}
