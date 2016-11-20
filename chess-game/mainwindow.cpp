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
    initBackgroundBoardColor();
    createLabels();

    setStyleSheet("background-color : rgb(220,200,140,100%);");

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
    playerLabelHeight = fieldSize/3;
    boardOffsetLeft = fieldSize/2;
    boardOffsetTop = playerLabelHeight*2;

    int formSize=boardOffsetLeft*2+fieldSize*BOARD_SIZE;

    this->setGeometry(QRect(
                          (screen.width()-formSize)/2,
                          (screen.height()-formSize)/2,
                          formSize,
                          formSize+playerLabelHeight));
}

void MainWindow::createBoard()
{
    Board = new CellButton*[BOARD_SIZE];

    for(int row=0;row<BOARD_SIZE;row++) {
        Board[row]=new CellButton[BOARD_SIZE];
        for(int col=0;col<BOARD_SIZE;col++) {
            Board[row][col].setParent(this);
            Board[row][col].setCoordinate(Coordinate(row,col));
            Board[row][col].setGeometry(QRect(boardOffsetLeft+col*fieldSize,boardOffsetTop+row*fieldSize,fieldSize,fieldSize));

            connect(&Board[row][col], SIGNAL (released()), this, SLOT (handlePieceClick()));
        }
    }
}

void MainWindow::createBackgroundBoard()
{
    BackgroundBoard = new CellButton*[BOARD_SIZE];

    for(int i=0;i<BOARD_SIZE;i++) {
        BackgroundBoard[i] = new CellButton[BOARD_SIZE];
        for(int j=0;j<BOARD_SIZE;j++) {
            BackgroundBoard[i][j].setCoordinate(Coordinate(i,j));
            BackgroundBoard[i][j].setParent(this);
            BackgroundBoard[i][j].setGeometry(QRect(boardOffsetLeft+j*fieldSize,boardOffsetTop+i*fieldSize,fieldSize,fieldSize));

            connect(&BackgroundBoard[i][j], SIGNAL (released()), this, SLOT (handleBackgroundClick()));
        }
    }
}

void MainWindow::initBackgroundBoardColor()
{
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            QString color = ( (i+j)%2 ? "rgba(130,130,130,100%)" : "rgba(220,220,220,100%)" );
            BackgroundBoard[i][j].setStyleSheet(getBackgroundStyleSheet(color));

            if(controller.getState().getPiece(Coordinate(i,j))==nullptr)
                Board[i][j].setStyleSheet(getBackgroundAndHoverStyleSheet("rgba(0,0,0,0%)","rgba(100,255,100,0%)"));
            else
                Board[i][j].setStyleSheet(getBackgroundAndHoverStyleSheet("rgba(0,0,0,0%)","rgba(100,255,100,50%)"));

        }
    }
}

void MainWindow::handleBackgroundClick()
{
    CellButton *cellButton = (CellButton*)sender();
    if(isSelected(cellButton->getCoordinate())) {
        controller.movePiece(selectedPieceCoordinate,cellButton->getCoordinate());
        drawState();
    }

    initBackgroundBoardColor();
    //unmarkCells();
    selectedPieceCoordinate = Coordinate(-1,-1);
    selectedCells.clear();

    this->setWindowTitle("PRESSED BACKGROUND");
}

void MainWindow::handlePieceClick()
{
    CellButton *cellButton = (CellButton*)sender();
    Piece *selectedPiece = controller.getState().getPiece(Coordinate(cellButton->getCoordinate().getRow(),cellButton->getCoordinate().getColumn()));

    if(selectedPiece==nullptr) {
        handleBackgroundClick();
        return;
    }

    initBackgroundBoardColor();
    //unmarkCells();

    if(isSelected(cellButton->getCoordinate())) {
        // TO-DO
        // takePiece method
    } else {

        if(selectedPiece->getColor() == controller.getState().getCurrentPlayer()->getColor()) {
            selectedPieceCoordinate = cellButton->getCoordinate();
            selectedCells = controller.getValidMoves(cellButton->getCoordinate());

            markCells();
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
        TopLabels[i].setGeometry(QRect(boardOffsetLeft+i*fieldSize,playerLabelHeight,fieldSize,playerLabelHeight));
    }

    BottomLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        BottomLabels[i].setParent(this);
        BottomLabels[i].setAlignment(Qt::AlignCenter);
        BottomLabels[i].setText(QString('a'+i));
        BottomLabels[i].setFont(QFont("Calibri",15,100));
        BottomLabels[i].setGeometry(QRect(boardOffsetLeft+i*fieldSize,boardOffsetTop+8*fieldSize,fieldSize,playerLabelHeight));
    }

    LeftLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        LeftLabels[i].setParent(this);
        LeftLabels[i].setAlignment(Qt::AlignCenter);
        LeftLabels[i].setText(QString('8'-i));
        LeftLabels[i].setFont(QFont("Calibri",15,100));
        LeftLabels[i].setGeometry(QRect(0,boardOffsetLeft+i*fieldSize,fieldSize/2,fieldSize));
    }

    RightLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        RightLabels[i].setParent(this);
        RightLabels[i].setAlignment(Qt::AlignCenter);
        RightLabels[i].setText(QString('8'-i));
        RightLabels[i].setFont(QFont("Calibri",15,100));
        RightLabels[i].setGeometry(QRect(boardOffsetLeft+8*fieldSize,boardOffsetTop+i*fieldSize,fieldSize/2,fieldSize));
    }
}

bool MainWindow::isSelected(Coordinate coordinate)
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
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
            if(piece == "") {
                Board[row][col].setIcon(QIcon());
                continue;
            }

            QPixmap qPixmap(":/figures/Images/"+piece+".png");
            Board[row][col].setIcon(QIcon(qPixmap));
            Board[row][col].setIconSize(qPixmap.rect().size());
        }
    }

    drawCurrentPlayer();
}

QString MainWindow::getBackgroundStyleSheet(QString color)
{
    return QString("QPushButton { background-color : ")+ color + "; border: 1px solid black;}";
}

QString MainWindow::getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor)
{
    return QString("QPushButton {background-color: "+backgroundColor+"} ")
            +"QPushButton:hover {background-color: "+hoverColor+";}";
}

void MainWindow::markCells()
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
        int row = selectedCells[i].getRow();
        int col = selectedCells[i].getColumn();
        BackgroundBoard[row][col].setStyleSheet(getBackgroundStyleSheet("rgba(50,255,50,100%)"));
    }
    BackgroundBoard[selectedPieceCoordinate.getRow()][selectedPieceCoordinate.getColumn()]
            .setStyleSheet(getBackgroundStyleSheet("rgba(100,200,100,100%)"));
}

void MainWindow::unmarkCells()
{
    int row;
    int col;
    QString color;

    for(unsigned int i=0;i<selectedCells.size();i++) {
        row = selectedCells[i].getRow();
        col = selectedCells[i].getColumn();
        color = ( (row+col)%2 ? "rgba(130,130,130,100%)" : "rgba(220,220,220,100%)" );
        BackgroundBoard[row][col].setStyleSheet(getBackgroundStyleSheet(color));
    }
    if(selectedPieceCoordinate.isInBoard()) {
        row = selectedPieceCoordinate.getRow();
        col = selectedPieceCoordinate.getColumn();
        color = ( (row+col)%2 ? "rgba(130,130,130,100%)" : "rgba(220,220,220,100%)" );
        BackgroundBoard[row][col].setStyleSheet(getBackgroundStyleSheet(color));
    }
}

void MainWindow::drawCurrentPlayer()
{
    const Player *player = controller.getState().getCurrentPlayer();
    QString PlayerName = "";
    Color color = cWhite;
    if(player!=nullptr) {
        PlayerName = QString(player->getName().c_str());
        color = player->getColor();
    }
    QString text = QString("Current player: ")+PlayerName;

    PlayerNameLabel.setParent(this);
    PlayerNameLabel.setAlignment(Qt::AlignLeft);
    PlayerNameLabel.setFont(QFont("Calibri",15,100));
    if(color == cBlack) {
        PlayerNameLabel.setStyleSheet("color: rgb(0,0,0,100%);");
        text += QString("(Black)");
    } else {
        PlayerNameLabel.setStyleSheet("color: rgb(10,200,10,100%);");
        text += QString("(White)");
    }

    PlayerNameLabel.setText(text);
    PlayerNameLabel.setGeometry(QRect(0,0,400,playerLabelHeight));

}
