#ifndef CHOOSEPIECEDIALOG_H
#define CHOOSEPIECEDIALOG_H

#include <QDialog>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>

#include "cellbutton.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

namespace Ui {
class ChoosePieceDialog;
}

class ChoosePieceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosePieceDialog(QWidget *parent = 0);
    ~ChoosePieceDialog();

private:
    CellButton *Pieces;
    CellButton *PiecesBackground;
    CellButton *SelectedPiece;
    QLabel *LabelCaption;
    QPushButton *ButtonChoose;
    Ui::ChoosePieceDialog *ui;

    void setWindowSize();
    void initCaption();
    void initPieces();
    void initChooseButton();
    void setPiece(Piece *piece, int idx);

private slots:
    void handlePieceClick();
    void handleChooseClick();
};

#endif // CHOOSEPIECEDIALOG_H
