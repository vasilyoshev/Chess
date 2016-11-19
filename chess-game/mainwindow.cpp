#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowSize();

    createBackgroundBoard();
    createBoard();
    createLabels();

    drawState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWindowSize()
{
    QRect screen = QApplication::desktop()->screenGeometry();

    fieldSize = screen.height()*6/8/9;
    offsetLeft=fieldSize/2;

    int formSize=offsetLeft*2+fieldSize*BOARD_SIZE;
    this->setGeometry(QRect((screen.width()-formSize)/2,(screen.height()-formSize)/2,formSize,formSize));
}

void MainWindow::createBoard()
{
    Board = new CellButton*[BOARD_SIZE];

    for(int row=0;row<BOARD_SIZE;row++) {
        Board[row]=new CellButton[BOARD_SIZE];
        for(int col=0;col<BOARD_SIZE;col++) {
            if(controller.getState().getPiece(Coordinate(row,col))==nullptr)
                continue;

            Board[row][col].setParent(this);
            Board[row][col].setCoordinate(Coordinate(row,col));
            Board[row][col].setGeometry(QRect(offsetLeft+col*fieldSize,offsetLeft+row*fieldSize,fieldSize,fieldSize));
            Board[row][col].setStyleSheet(QString("QPushButton {background-color: rgba(0,0,0,0%);} ")+
                                          "QPushButton:pressed {background-color: rgba(100,255,100,50%);}");

            connect(&Board[row][col], SIGNAL (released()), this, SLOT (handlePieceClick()));
        }
    }
}

void MainWindow::createBackgroundBoard()
{
    BackgroundBoard = new QPushButton*[BOARD_SIZE];

    for(int i=0;i<BOARD_SIZE;i++) {
        BackgroundBoard[i] = new QPushButton[BOARD_SIZE];
        for(int j=0;j<BOARD_SIZE;j++) {
            BackgroundBoard[i][j].setParent(this);
            BackgroundBoard[i][j].setGeometry(QRect(offsetLeft+j*fieldSize,offsetLeft+i*fieldSize,fieldSize,fieldSize));

            connect(&BackgroundBoard[i][j], SIGNAL (released()), this, SLOT (handleBackgroundClick()));
        }
    }

    initBackgroundBoardColor();
}

void MainWindow::initBackgroundBoardColor()
{
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            QString color = ( (i+j)%2 ? "brown" : "yellow" );
            BackgroundBoard[i][j].setStyleSheet("QPushButton { background-color : "+color+"; color : blue; border: 2px solid grey;} ");
        }
    }
}

void MainWindow::handleBackgroundClick()
{
    initBackgroundBoardColor();

    this->setWindowTitle("PRESSED BACKGROUND");
}

void MainWindow::handlePieceClick()
{
    initBackgroundBoardColor();
    CellButton *cellButton = (CellButton*)sender();

    if(isSelected(cellButton->getCoordinate())) {
        controller.movePiece(*selectedPieceCoordinate,cellButton->getCoordinate());
        drawState();
    } else {
        selectedCells = controller.getValidMoves(cellButton->getCoordinate());
        for(int i=0;i<selectedCells.size();i++) {
            int row = selectedCells[i].getRow();
            int col = selectedCells[i].getColumn();
            BackgroundBoard[row][col].setStyleSheet("QPushButton { background-color : green; color : blue; border: 2px solid grey;} ");
        }
    }

    this->setWindowTitle("PRESSED PIECE");
}

QString MainWindow::getPieceFileName(Piece *p)
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

void MainWindow::createLabels()
{
    TopLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        TopLabels[i].setParent(this);
        TopLabels[i].setAlignment(Qt::AlignCenter);
        TopLabels[i].setText(QString('a'+i));
        TopLabels[i].setFont(QFont("Calibri",15,100));
        TopLabels[i].setGeometry(QRect(offsetLeft+i*fieldSize,0,fieldSize,offsetLeft));
    }

    BottomLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        BottomLabels[i].setParent(this);
        BottomLabels[i].setAlignment(Qt::AlignCenter);
        BottomLabels[i].setText(QString('a'+i));
        BottomLabels[i].setFont(QFont("Calibri",15,100));
        BottomLabels[i].setGeometry(QRect(offsetLeft+i*fieldSize,offsetLeft+8*fieldSize,fieldSize,offsetLeft));
    }

    LeftLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        LeftLabels[i].setParent(this);
        LeftLabels[i].setAlignment(Qt::AlignCenter);
        LeftLabels[i].setText(QString('8'-i));
        LeftLabels[i].setFont(QFont("Calibri",15,100));
        LeftLabels[i].setGeometry(QRect(0,offsetLeft+i*fieldSize,offsetLeft,fieldSize));
    }

    RightLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        RightLabels[i].setParent(this);
        RightLabels[i].setAlignment(Qt::AlignCenter);
        RightLabels[i].setText(QString('8'-i));
        RightLabels[i].setFont(QFont("Calibri",15,100));
        RightLabels[i].setGeometry(QRect(offsetLeft+8*fieldSize,offsetLeft+i*fieldSize,offsetLeft,fieldSize));
    }
}

bool MainWindow::isSelected(Coordinate coordinate)
{
    for(int i=0;i<selectedCells.size();i++) {
        if(coordinate==selectedCells[i])
            return true;
    }

    return false;
}

void MainWindow::drawState()
{
    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {


            Piece *p = controller.getState().getBoard()[row][col].getPiece();
            QString piece = getPieceFileName(p);
            if(piece == "")
                continue;

            QPixmap qPixmap(":/figures/Images/"+piece+".png");
            Board[row][col].setIcon(QIcon(qPixmap));
            Board[row][col].setIconSize(qPixmap.rect().size());
        }
    }
}
