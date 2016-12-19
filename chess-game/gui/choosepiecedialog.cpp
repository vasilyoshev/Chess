#include "choosepiecedialog.h"
#include "ui_choosepiecedialog.h"

#include <memory>

#include "uihelperfunc.h"

const int BOARD_SIZE = 6;
int fieldSize;
int boardOffsetLeft;
int boardOffsetTop;

ChoosePieceDialog::ChoosePieceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosePieceDialog)
{
    ui->setupUi(this);

    setWindowSize();
    setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());

    initCaption();
    initPieces();
    initChooseButton();
}

ChoosePieceDialog::~ChoosePieceDialog() {
    delete ui;

    delete[] Pieces;
    delete[] PiecesBackground;
    delete SelectedPiece;
}


void ChoosePieceDialog::setWindowSize() {
    QRect screen = QApplication::desktop()->screenGeometry();

    fieldSize = screen.height()*6/BOARD_SIZE/9;
    boardOffsetLeft = fieldSize/2;
    boardOffsetTop = fieldSize/3*2;
    int formSize=boardOffsetLeft*2+fieldSize*BOARD_SIZE;

    this->setGeometry(QRect(
                          (screen.width()-formSize)/2,
                          (screen.height()-formSize)/2,
                          formSize,
                          formSize/1.5));
}

void ChoosePieceDialog::initCaption() {
    LabelCaption = new QLabel();
    LabelCaption->setParent(this);
    LabelCaption->setGeometry(QRect(
                                boardOffsetLeft,
                                0,
                                fieldSize*6,
                                boardOffsetTop));
    LabelCaption->setText("Choose a piece");
    LabelCaption->setFont(QFont("Calibri",20,100));
    LabelCaption->setAlignment(Qt::AlignCenter);
}

void ChoosePieceDialog::initPieces() {
    SelectedPiece = new CellButton();
    SelectedPiece->setParent(this);
    SelectedPiece->setGeometry(QRect(
                                boardOffsetLeft+BOARD_SIZE/2*fieldSize-fieldSize/2,
                                boardOffsetTop+fieldSize+fieldSize/2,
                                fieldSize,
                                fieldSize));
    SelectedPiece->setEnabled(false);
    SelectedPiece->setStyleSheet("background-color : rgb(220,200,140,100%); border: 2px solid black;");


    Pieces = new CellButton[BOARD_SIZE];
    PiecesBackground = new CellButton[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
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
    piece = new Pawn(cWhite);
    setPiece(piece,0);
    delete piece;
    piece = new Knight(cWhite);
    setPiece(piece,1);
    delete piece;
    piece = new Bishop(cWhite);
    setPiece(piece,2);
    delete piece;
    piece = new Rook(cWhite);
    setPiece(piece,3);
    delete piece;
    piece = new Queen(cWhite);
    setPiece(piece,4);
    delete piece;
    piece = new King(cWhite);
    setPiece(piece,5);
    delete piece;
}

void ChoosePieceDialog::setPiece(Piece *piecePtr, int idx) {
    QString piece = UIHelperFunc::getPieceFileName(&*piecePtr);
    QPixmap qPixmap(":/figures/Images/"+piece+".png");
    Pieces[idx].setIcon(QIcon(qPixmap));
    Pieces[idx].setIconSize(qPixmap.rect().size());
}

void ChoosePieceDialog::initChooseButton() {
    ButtonChoose = new QPushButton();
    ButtonChoose->setParent(this);
    ButtonChoose->setGeometry(QRect(
                                boardOffsetLeft+BOARD_SIZE/2*fieldSize-fieldSize,
                                boardOffsetTop+fieldSize+fieldSize*2,
                                fieldSize*2,
                                fieldSize/2));
    ButtonChoose->setEnabled(false);
    ButtonChoose->setText("Choose");
    ButtonChoose->setFont(QFont("Calibri",15,100));
    ButtonChoose->setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());
    connect(ButtonChoose, SIGNAL (released()), this, SLOT (handleChooseClick()));
}

void ChoosePieceDialog::handlePieceClick() {
    CellButton *cellButton = (CellButton*)sender();

    SelectedPiece->setIcon(cellButton->icon());
    SelectedPiece->setIconSize(cellButton->iconSize());

    ButtonChoose->setEnabled(true);
    ButtonChoose->setStyleSheet("background-color : rgb(204,255,153,100%);");
    setStyleSheet("background-color : rgb(230,255,204,100%);");
    SelectedPiece->setStyleSheet("background-color : rgb(255,255,51,100%); border: 2px solid black;");
}

void ChoosePieceDialog::handleChooseClick() {

}
