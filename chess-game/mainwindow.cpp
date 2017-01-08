#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameoptionswindow.h"
#include "choosepiecedialog.h"

#include <QDialogButtonBox>

int formSize;

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

    setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());

    /// TO-DO use the forms when necessary

    /*ChoosePieceDialog choosePieceDialog;
    choosePieceDialog.setModal(true);
    choosePieceDialog.exec();
    exit(0);*/


    GameOptionsWindow gameOptionsWindow;
    gameOptionsWindow.setModal(true);
    int result = gameOptionsWindow.exec();
    if(result != 1) {
        exit(0);
    }

    controller.setFirstPlayer(gameOptionsWindow.getFirstPlayerName(), gameOptionsWindow.getSelectedColor());
    controller.setSecondPlayer(gameOptionsWindow.getSecondPlayerName(), ColorUtils::getOppositeColor(gameOptionsWindow.getSelectedColor()));
    controller.setGameType(gameOptionsWindow.getSelectedGameType());
    controller.initStartingPlayer();

    // TO-DO get the result from the options dialog and pass to the controller...

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

    formSize=boardOffsetLeft*2+fieldSize*BOARD_SIZE;

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

            connect(&BackgroundBoard[i][j], SIGNAL (released()), this, SLOT (handleValidMoveClick()));
        }
    }
}

void MainWindow::initBackgroundBoardColor()
{
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            QString color = ( (i+j)%2 ? "rgba(130,130,130,100%)" : "rgba(220,220,220,100%)" );
            BackgroundBoard[i][j].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet(color));

            if(controller.getState().getPiece(Coordinate(i,j))==nullptr)
                Board[i][j].setStyleSheet(UIHelperFunc::getBackgroundAndHoverStyleSheet("rgba(0,0,0,0%)","rgba(100,255,100,0%)"));
            else
                Board[i][j].setStyleSheet(UIHelperFunc::getBackgroundAndHoverStyleSheet("rgba(0,0,0,0%)","rgba(100,255,100,50%)"));

        }
    }
}

void MainWindow::handleValidMoveClick()
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
        handleValidMoveClick();
        return;
    }

    initBackgroundBoardColor();
    //unmarkCells();

    if(isSelected(cellButton->getCoordinate())) {
        // TO-DO
        // takePiece method
        controller.movePiece(selectedPieceCoordinate,cellButton->getCoordinate());
        drawState();
        selectedPieceCoordinate = Coordinate(-1,-1);
        selectedCells.clear();
    } else {
        if(selectedPiece->getColor() == controller.getState().getCurrentPlayer()->getColor()) {
            selectedPieceCoordinate = cellButton->getCoordinate();
            selectedCells = controller.getValidMoves(cellButton->getCoordinate());

            markCells();
        }
    }

    this->setWindowTitle("PRESSED PIECE");
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

    PlayerCheckLabel.setParent(this);
    PlayerCheckLabel.setAlignment(Qt::AlignLeft);
    PlayerCheckLabel.setFont(QFont("Calibri",20,100));
    PlayerCheckLabel.setStyleSheet("color: rgb(255,10,50,100%);");
    PlayerCheckLabel.setText(QString("YOU ARE IN CHESS"));
    PlayerCheckLabel.setGeometry(QRect(formSize-250,0,250,playerLabelHeight));
    PlayerCheckLabel.setVisible(false);
}

void MainWindow::drawState()
{
    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            Piece *p = controller.getState().getBoard()[row][col].getPiece();
            QString piece = UIHelperFunc::getPieceFileName(p);
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

    if( controller.getState().getCurrentPlayer()->isInCheckmate() ) {
        showGameOver();
    }
}

void MainWindow::markCells()
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
        int row = selectedCells[i].getRow();
        int col = selectedCells[i].getColumn();
        BackgroundBoard[row][col].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet("rgba(50,255,50,100%)"));
    }
    BackgroundBoard[selectedPieceCoordinate.getRow()][selectedPieceCoordinate.getColumn()]
            .setStyleSheet(UIHelperFunc::getBackgroundStyleSheet("rgba(100,200,100,100%)"));
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
        BackgroundBoard[row][col].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet(color));
    }
    if(selectedPieceCoordinate.isInBoard()) {
        row = selectedPieceCoordinate.getRow();
        col = selectedPieceCoordinate.getColumn();
        color = ( (row+col)%2 ? "rgba(130,130,130,100%)" : "rgba(220,220,220,100%)" );
        BackgroundBoard[row][col].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet(color));
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
    PlayerNameLabel.setFont(QFont("Calibri",20,100));
    if(color == cBlack) {
        PlayerNameLabel.setStyleSheet("color: rgb(0,0,0,100%);");
        text += QString("(Black)");
    } else {
        PlayerNameLabel.setStyleSheet("color: rgb(10,200,10,100%);");
        text += QString("(White)");
    }
    PlayerNameLabel.setText(text);
    PlayerNameLabel.setGeometry(QRect(boardOffsetLeft,0,400,playerLabelHeight));


    // TO-DO check if check, then show/hide label
    PlayerCheckLabel.setVisible( controller.getState().getCurrentPlayer()->isInCheck() );
}


bool MainWindow::isSelected(Coordinate coordinate)
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
        if(coordinate==selectedCells[i])
            return true;
    }

    return false;
}

void MainWindow::showGameOver() {
    QMessageBox msgBox;
    msgBox.setText("Game over");
    std::string message = controller.getState().getCurrentPlayer()->getName() + ", you won the game! Nice job!";
    msgBox.setInformativeText(message.c_str());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    exit(0);
}

