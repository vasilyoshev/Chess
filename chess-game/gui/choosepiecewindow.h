#ifndef CHOOSEPIECEWINDOW_H
#define CHOOSEPIECEWINDOW_H

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
class ChoosePieceWindow;
}

/**
 * @brief The ChoosePieceWindow class
 *
 * This class is used to show a dialog window that appears when the user wants to choose a piece
 * that will replace the pawn which has reached the end of the grid.
 */
class ChoosePieceWindow : public QDialog {
    Q_OBJECT

public:    

    explicit ChoosePieceWindow(QWidget *parent = 0);
    ~ChoosePieceWindow();

    static Piece::PieceType getSelectedPieceType();

private:
CellButton *Pieces;
CellButton *PiecesBackground;
CellButton *SelectedPiece;
QLabel *LabelCaption;
QPushButton *ButtonChoose;
Ui::ChoosePieceWindow *ui;
static Piece::PieceType selectedPieceType;

    void setWindowSize();
    void initCaption();
    void initPieces();
    void initChooseButton();
    void setPiece(Piece *piece, int idx);

private slots:
    void handlePieceClick();
    void handleChooseClick();
};

#endif // CHOOSEPIECEWINDOW_H
