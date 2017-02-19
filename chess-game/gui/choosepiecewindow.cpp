#include "choosepiecewindow.h"
#include "ui_choosepiecewindow.h"

#include <memory>

#include "uihelperfunc.h"

const int NUMBER_OF_PIECES = 4;
int fieldSize;
int boardOffsetLeft;
int boardOffsetTop;

extern Piece::PieceType ChoosePieceWindow::selectedPieceType;

ChoosePieceWindow::ChoosePieceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosePieceWindow)
{
    ui->setupUi(this);

    setWindowSize();
    setWindowTitle("Pawn Promotion");
    setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());
    setWindowFlags(Qt::WindowTitleHint);
    setResult(QDialog::Rejected);

    initCaption();
    initPieces();
    initChooseButton();
}

ChoosePieceWindow::~ChoosePieceWindow() {
    delete ui;

    delete[] Pieces;
    delete[] PiecesBackground;
    delete SelectedPiece;
    delete ButtonChoose;
}

/**
 * @brief ChoosePieceWindow::setWindowSize
 *
 * Initializes the size of the dialog.
 */
void ChoosePieceWindow::setWindowSize() {
    QRect screen = QApplication::desktop()->screenGeometry();

    fieldSize = screen.height() / 9;
    boardOffsetLeft = fieldSize / 2;
    boardOffsetTop = fieldSize / 3 * 2;
    int formSize = boardOffsetLeft * 2 + fieldSize * NUMBER_OF_PIECES;

    this->setGeometry(QRect(
                          (screen.width() - formSize) /2 ,
                          (screen.height() - formSize) / 2,
                          formSize,
                          formSize / 1.25));
}

/**
 * @brief ChoosePieceWindow::initCaption
 *
 * Initializes a Label with caption of the dialog.
 */
void ChoosePieceWindow::initCaption() {
    LabelCaption = new QLabel();
    LabelCaption->setParent(this);
    LabelCaption->setGeometry(QRect(
                                boardOffsetLeft,
                                0,
                                fieldSize*NUMBER_OF_PIECES,
                                boardOffsetTop));
    LabelCaption->setText("Choose a piece");
    LabelCaption->setFont(QFont("Calibri",20,100));
    LabelCaption->setAlignment(Qt::AlignCenter);
}

/**
 * @brief ChoosePieceWindow::initPieces
 *
 * Initializes the pieces on the fields.
 */
void ChoosePieceWindow::initPieces() {
    SelectedPiece = new CellButton();
    SelectedPiece->setParent(this);
    SelectedPiece->setGeometry(QRect(
                                boardOffsetLeft+NUMBER_OF_PIECES/2*fieldSize - fieldSize/2,
                                boardOffsetTop+fieldSize*1.25,
                                fieldSize,
                                fieldSize));
    SelectedPiece->setEnabled(false);
    SelectedPiece->setStyleSheet("background-color : rgb(220,200,140,100%); border: 2px solid black;");


    Pieces = new CellButton[NUMBER_OF_PIECES];
    PiecesBackground = new CellButton[NUMBER_OF_PIECES];
    for(int i=0;i<NUMBER_OF_PIECES;i++) {
        PiecesBackground[i].setParent(this);
        PiecesBackground[i].setGeometry(QRect(
                                    boardOffsetLeft+i*fieldSize,
                                    boardOffsetTop,
                                    fieldSize,
                                    fieldSize));
        PiecesBackground[i].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet()));

        Pieces[i].setParent(this);
        Pieces[i].setGeometry(QRect(
                                    boardOffsetLeft+i*fieldSize,
                                    boardOffsetTop,
                                    fieldSize,
                                    fieldSize));
        Pieces[i].setStyleSheet(UIHelperFunc::getBackgroundAndHoverStyleSheet("rgba(0,0,0,0%)","rgba(100,255,100,50%)"));
        connect(&Pieces[i], SIGNAL (released()), this, SLOT (handlePieceClick()));
    }

    Piece *piece = nullptr;
    piece = new Knight(cWhite);
    setPiece(piece,0);
    delete piece;
    piece = new Bishop(cWhite);
    setPiece(piece,1);
    delete piece;
    piece = new Rook(cWhite);
    setPiece(piece,2);
    delete piece;
    piece = new Queen(cWhite);
    setPiece(piece,3);
    delete piece;
}

/**
 * @brief ChoosePieceWindow::setPiece
 * @param piecePtr Piece type.
 * @param idx Index of field to be put.
 *
 * Sets the given piece image on the provided index.
 */
void ChoosePieceWindow::setPiece(Piece *piecePtr, int idx) {
    QString piece = UIHelperFunc::getPieceFileName(piecePtr);
    QPixmap qPixmap(":/figures/Images/"+piece+".png");
    Pieces[idx].setIcon(QIcon(qPixmap));
    Pieces[idx].setIconSize(qPixmap.rect().size());
    Pieces[idx].setPieceType(piecePtr->getType());
}

/**
 * @brief ChoosePieceWindow::initChooseButton
 *
 * Button that submits the choose action of the user.
 */
void ChoosePieceWindow::initChooseButton() {
    ButtonChoose = new QPushButton();
    ButtonChoose->setParent(this);
    ButtonChoose->setGeometry(QRect(
                                boardOffsetLeft+NUMBER_OF_PIECES/2*fieldSize - fieldSize,
                                boardOffsetTop+fieldSize*2.5,
                                fieldSize*2,
                                fieldSize/2));
    ButtonChoose->setEnabled(false);
    ButtonChoose->setText("Choose");
    ButtonChoose->setFont(QFont("Calibri",15,100));
    ButtonChoose->setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());
    connect(ButtonChoose, SIGNAL (released()), this, SLOT (handleChooseClick()));
}

/**
 * @brief ChoosePieceWindow::handlePieceClick
 *
 * This method highlights the piece being clicked.
 */
void ChoosePieceWindow::handlePieceClick() {
    CellButton *cellButton = (CellButton*)sender();

    SelectedPiece->setIcon(cellButton->icon());
    SelectedPiece->setIconSize(cellButton->iconSize());

    ButtonChoose->setEnabled(true);
    ButtonChoose->setStyleSheet("background-color : rgb(204,255,153,100%);");
    setStyleSheet("background-color : rgb(230,255,204,100%);");
    SelectedPiece->setStyleSheet("background-color : rgb(255,255,51,100%); border: 2px solid black;");

    selectedPieceType = cellButton->getPieceType();
}

/**
 * @brief ChoosePieceWindow::handleChooseClick
 *
 * When the user clicks the submit button, the dialog closes, and the game continues.
 */
void ChoosePieceWindow::handleChooseClick() {
    QDialog::accept();
}

/**
 * @brief ChoosePieceWindow::getSelectedPieceType
 * @return Returns the selected piece type for pawn promotion.
 */
Piece::PieceType ChoosePieceWindow::getSelectedPieceType() {
    return selectedPieceType;
}
