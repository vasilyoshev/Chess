#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameoptionswindow.h"
#include "choosepiecewindow.h"

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

    GameOptionsWindow gameOptionsWindow;
    gameOptionsWindow.setModal(true);
    int result = gameOptionsWindow.exec();
    if(result != 1) {
        exit(0);
    }

    controller.setFirstPlayer(gameOptionsWindow.getFirstPlayerName(), gameOptionsWindow.getSelectedColor());
    controller.setSecondPlayer(gameOptionsWindow.getSecondPlayerName(), ColorUtils::getOppositeColor(gameOptionsWindow.getSelectedColor()));
    controller.setGameType(gameOptionsWindow.getSelectedGameType());
    controller.setWhitePlayerInTurn();

    drawState(); // draw initial state
}

MainWindow::~MainWindow()
{
    delete ui;

    // Board

    for(int i=0;i<BOARD_SIZE;i++) {
        delete[] Board[i];
        delete[] BackgroundBoard[i];
    }
    delete[] Board;
    delete[] BackgroundBoard;

    // Labels

    delete[] TopLabels;
    delete[] BottomLabels;
    delete[] LeftLabels;
    delete[] RightLabels;
}

/**
 * @brief MainWindow::setWindowSize
 *
 * Calculates the size of the labels, board, cells on the board and the window.
 */
void MainWindow::setWindowSize()
{
    QRect screen = QApplication::desktop()->screenGeometry();

    /** Assuming that the screen is wide(i.e. the width is greater than the height)
     * we set the side of the field to be 1/12 of the height.
     **/
    fieldSize = screen.height() / 12;
    playerLabelHeight = fieldSize / 3;
    boardOffsetLeft = fieldSize / 2;
    boardOffsetTop = playerLabelHeight * 2;
    formSize = boardOffsetLeft * 2 + fieldSize * BOARD_SIZE;

    this->setGeometry(QRect(
                          (screen.width()-formSize)/2, // pixels from left
                          (screen.height()-formSize)/2, // pixels from top
                          formSize, // width
                          formSize+playerLabelHeight)); // height
}

/**
 * @brief MainWindow::createBoard
 *
 * Creates the board with buttons that are used to contain pieces.
 */
void MainWindow::createBoard()
{
    Board = new CellButton*[BOARD_SIZE];

    for(int row=0;row<BOARD_SIZE;row++) {
        Board[row]=new CellButton[BOARD_SIZE];
        for(int col=0;col<BOARD_SIZE;col++) {
            Board[row][col].setParent(this);
            Board[row][col].setCoordinate(Coordinate(row, col));
            Board[row][col].setGeometry(QRect(boardOffsetLeft+col*fieldSize, boardOffsetTop+row*fieldSize, fieldSize, fieldSize));

            connect(&Board[row][col], SIGNAL (released()), this, SLOT (handlePieceClick()));
        }
    }
}

/**
 * @brief MainWindow::createBoard
 *
 * Creates the board with buttons that are in the background i.e. that have no pieces on them.
 */
void MainWindow::createBackgroundBoard()
{
    BackgroundBoard = new CellButton*[BOARD_SIZE];

    for(int i=0;i<BOARD_SIZE;i++) {
        BackgroundBoard[i] = new CellButton[BOARD_SIZE];
        for(int j=0;j<BOARD_SIZE;j++) {
            BackgroundBoard[i][j].setCoordinate(Coordinate(i, j));
            BackgroundBoard[i][j].setParent(this);
            BackgroundBoard[i][j].setGeometry(QRect(boardOffsetLeft+j*fieldSize, boardOffsetTop+i*fieldSize, fieldSize, fieldSize));

            connect(&BackgroundBoard[i][j], SIGNAL (released()), this, SLOT (handleBackgroundAndHighlightedFields()));
        }
    }
}

/**
 * @brief MainWindow::createBoard
 *
 * Sets the color of the background buttons to the traditional chess-like color.
 * This way, the method removes any highlighted fields.
 */
void MainWindow::initBackgroundBoardColor()
{
    for(int i=0;i<BOARD_SIZE;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            QString color = ( (i+j)%2 ? "rgba(130, 130, 130, 100%)" : "rgba(220, 220, 220, 100%)" );
            BackgroundBoard[i][j].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet(color));

            if(controller.getPiece(Coordinate(i, j))==nullptr)
                Board[i][j].setStyleSheet(UIHelperFunc::getBackgroundAndHoverStyleSheet("rgba(0, 0, 0 , 0%)", "rgba(100, 255, 100, 0%)"));
            else
                Board[i][j].setStyleSheet(UIHelperFunc::getBackgroundAndHoverStyleSheet("rgba(0, 0, 0, 0%)", "rgba(100, 255, 100, 50%)"));

        }
    }
}

/**
 * @brief MainWindow::handleBackgroundAndHighlightedFields
 *
 * When background field or highlighted field is clicked, this method is called.
 * One method is used, since the actions taken when those situations occur are taken are the same.
 */
void MainWindow::handleBackgroundAndHighlightedFields()
{
    CellButton *cellButton = (CellButton*)sender();
    if(isSelected(cellButton->getCoordinate())) {
        controller.movePiece(selectedPieceCoordinate, cellButton->getCoordinate());
        drawState();
    }

    initBackgroundBoardColor();
    selectedPieceCoordinate = Coordinate(-1, -1);
    selectedCells.clear();
}

/**
 * @brief MainWindow::handlePieceClick
 *
 * This method is called when a piece is clicked.
 */
void MainWindow::handlePieceClick()
{
    CellButton *cellButton = (CellButton*)sender();
    Piece* selectedPiece = controller.getPiece(cellButton->getCoordinate());
    bool isBackgroundClicked = (selectedPiece==nullptr ? true : false);

    if(isBackgroundClicked || isSelected(cellButton->getCoordinate())) {
        handleBackgroundAndHighlightedFields();
    } else {
        if(selectedPiece->getColor() == controller.getCurrentPlayer()->getColor()) {
            selectedPieceCoordinate = cellButton->getCoordinate();
            selectedCells = controller.getValidMoves(cellButton->getCoordinate());

            initBackgroundBoardColor();
            highlightCells();
        }
    }
}

/**
 * @brief MainWindow::createLabels
 *
 * Initializes the labels around the board that show the "name" of the cell.
 * For example: a3 or b7.
 *
 * Also initializes the label for the "check" and "checkmate" status.
 */
void MainWindow::createLabels()
{
    TopLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        TopLabels[i].setParent(this);
        TopLabels[i].setAlignment(Qt::AlignCenter);
        TopLabels[i].setText(QString('a'+i));
        TopLabels[i].setFont(QFont("Calibri", 15, 100));
        TopLabels[i].setGeometry(QRect(boardOffsetLeft+i*fieldSize, playerLabelHeight, fieldSize, playerLabelHeight));
    }

    BottomLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        BottomLabels[i].setParent(this);
        BottomLabels[i].setAlignment(Qt::AlignCenter);
        BottomLabels[i].setText(QString('a'+i));
        BottomLabels[i].setFont(QFont("Calibri", 15, 100));
        BottomLabels[i].setGeometry(QRect(boardOffsetLeft+i*fieldSize, boardOffsetTop+8*fieldSize, fieldSize, playerLabelHeight));
    }

    LeftLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        LeftLabels[i].setParent(this);
        LeftLabels[i].setAlignment(Qt::AlignCenter);
        LeftLabels[i].setText(QString('8'-i));
        LeftLabels[i].setFont(QFont("Calibri", 15, 100));
        LeftLabels[i].setGeometry(QRect(0, boardOffsetLeft+i*fieldSize, fieldSize/2, fieldSize));
    }

    RightLabels = new QLabel[BOARD_SIZE];
    for(int i=0;i<BOARD_SIZE;i++) {
        RightLabels[i].setParent(this);
        RightLabels[i].setAlignment(Qt::AlignCenter);
        RightLabels[i].setText(QString('8'-i));
        RightLabels[i].setFont(QFont("Calibri", 15, 100));
        RightLabels[i].setGeometry(QRect(boardOffsetLeft+8*fieldSize, boardOffsetTop+i*fieldSize, fieldSize/2, fieldSize));
    }

    PlayerCheckLabel.setParent(this);
    PlayerCheckLabel.setAlignment(Qt::AlignLeft);
    PlayerCheckLabel.setFont(QFont("Calibri", 20, 100));
    PlayerCheckLabel.setStyleSheet("color: rgb(255, 10, 50, 100%);");
    PlayerCheckLabel.setText(QString("YOU ARE IN CHESS"));
    PlayerCheckLabel.setGeometry(QRect(formSize-250, 0, 250, playerLabelHeight));
    PlayerCheckLabel.setVisible(false);
}

/**
 * @brief MainWindow::drawState
 *
 * Draws the current state: all pieces currently on the board, the status of the game, and which player is on turn.
 *
 * Checks wether the game is in Checkmate state or it has a pawn promotion.
 *
 */
void MainWindow::drawState()
{
    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            Piece *p = controller.getPiece(Coordinate(row, col));
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

    if( controller.getCurrentPlayer()->isInCheckmate() ) {
        showGameOver();
    } else if( controller.isInPawnPromotion() )  {
        ChoosePieceWindow choosePieceWindow;
        choosePieceWindow.setModal(true);

        while( choosePieceWindow.exec()!=1 ) {
            // endless
        }

        controller.promotePawn( ChoosePieceWindow::getSelectedPieceType() ); // pawnPromotion should return false after this command

        drawState();
    }
}

/**
 * @brief MainWindow::highlightCells
 *
 * Highlights the selected cells of possible moves.
 *
 * This method assumes that the array "selectedCells" is already filled.
 */
void MainWindow::highlightCells()
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
        int row = selectedCells[i].getRow();
        int col = selectedCells[i].getColumn();
        BackgroundBoard[row][col].setStyleSheet(UIHelperFunc::getBackgroundStyleSheet("rgba(50, 255, 50, 100%)"));
    }
    BackgroundBoard[selectedPieceCoordinate.getRow()][selectedPieceCoordinate.getColumn()]
            .setStyleSheet(UIHelperFunc::getBackgroundStyleSheet("rgba(100, 200, 100, 100%)"));
}

/**
 * @brief MainWindow::drawCurrentPlayer
 *
 * Shows which player is currently on turn.
 */
void MainWindow::drawCurrentPlayer()
{
    const Player *player = controller.getCurrentPlayer();
    QString PlayerName = "";
    Color color = cWhite;
    if(player!=nullptr) {
        PlayerName = QString(player->getName().c_str());
        color = player->getColor();
    }
    QString text = QString("Current player: ")+PlayerName;

    PlayerNameLabel.setParent(this);
    PlayerNameLabel.setAlignment(Qt::AlignLeft);
    QRect screen = QApplication::desktop()->screenGeometry();
    double fontCoefficient = screen.height()*1.0/1080;
    PlayerNameLabel.setFont(QFont("Calibri", 20*fontCoefficient, 100));
    if(color == cBlack) {
        PlayerNameLabel.setStyleSheet("color: rgb(0, 0, 0, 100%);");
        text += QString("(Black)");
    } else {
        PlayerNameLabel.setStyleSheet("color: rgb(10, 200, 10, 100%);");
        text += QString("(White)");
    }
    PlayerNameLabel.setText(text);
    PlayerNameLabel.setGeometry(QRect(boardOffsetLeft, 0, 400, playerLabelHeight));

    PlayerCheckLabel.setVisible( controller.getCurrentPlayer()->isInCheck() );
}

/**
 * @brief MainWindow::isSelected
 * @param coordinate The coordinates to be checked.
 * @return Returns true if selected, false otherwise.
 *
 * Checks if the cell at the provided coordinates is highlighted(selected).
 */
bool MainWindow::isSelected(Coordinate coordinate)
{
    for(unsigned int i=0;i<selectedCells.size();i++) {
        if(coordinate==selectedCells[i])
            return true;
    }

    return false;
}

/**
 * @brief MainWindow::showGameOver
 *
 * Opens a dialog that alerts for a finished game and shows additional information about the game.
 */
void MainWindow::showGameOver() {
    QMessageBox msgBox;
    msgBox.setText("Game over");
    std::string message = controller.getCurrentPlayer()->getName() + ", you lost the game!";
    msgBox.setInformativeText(message.c_str());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    exit(0);
}
