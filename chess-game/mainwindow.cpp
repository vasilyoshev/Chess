#include "mainwindow.h"
#include "ui_mainwindow.h"

const int BOARD_SIZE = 8;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowSize();

    createBackgroundBoard();
    createBoard();
    createLabels();
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
    Board = new QPushButton*[BOARD_SIZE];

    for(int row=0;row<BOARD_SIZE;row++) {
        Board[row]=new QPushButton[BOARD_SIZE];
        for(int col=0;col<BOARD_SIZE;col++) {
            QString piece = getIdxName(row,col);
            if(piece == "")
                continue;

            QPixmap qPixmap(":/figures/Images/"+piece+".png");

            Board[row][col].setParent(this);
            Board[row][col].setGeometry(QRect(offsetLeft+col*fieldSize,offsetLeft+row*fieldSize,fieldSize,fieldSize));
            Board[row][col].setIcon(QIcon(qPixmap));
            Board[row][col].setIconSize(qPixmap.rect().size());
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

            QString color = ( (i+j)%2 ? "brown" : "yellow" );
            BackgroundBoard[i][j].setStyleSheet("QPushButton { background-color : "+color+"; color : blue; border: 2px solid grey;} ");

            connect(&BackgroundBoard[i][j], SIGNAL (released()), this, SLOT (handleBackgroundClick()));
        }
    }
}

void MainWindow::handleBackgroundClick()
{
    this->setWindowTitle("PRESSED BACKGROUND");
}

void MainWindow::handlePieceClick()
{
    this->setWindowTitle("PRESSED PIECE");
}


QString MainWindow::getIdxName(int row,int col)
{
    QString Result;
    switch(col) {
        case    0   :
        case    7   :
            Result = "Top";
            break;
        case    1   :
        case    6   :
            Result = "Kon";
            break;
        case    2   :
        case    5   :
            Result = "Oficer";
            break;
        case    3   :
            Result = "Car";
            break;
        case    4   :
            Result = "Dama";
            break;
    }

    switch(row) {
        case    0   :
            return Result+"B";
        case    1   :
            return "PeshkaB";
        case    6   :
            return "PeshkaW";
        case    7   :
            return Result+"W";
        default:
            return "";
    }
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
