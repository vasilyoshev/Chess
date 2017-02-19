#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QMessageBox>

#include "controller.h"
#include "cellbutton.h"
#include "uihelperfunc.h"
#include "ai.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
Ui::MainWindow *ui;
int fieldSize;
int boardOffsetLeft;
int boardOffsetTop;
int playerLabelHeight;
CellButton **Board;
CellButton **BackgroundBoard;
QLabel *TopLabels, *RightLabels, *BottomLabels, *LeftLabels;
QLabel PlayerNameLabel;
QLabel PlayerCheckLabel;
vector<Coordinate> selectedCells;
Coordinate selectedPieceCoordinate;
Controller controller;

    // initialization functions
    void createBoard();
    void createBackgroundBoard();
    void createLabels();
    void initBackgroundBoardColor();

    // help functions
    bool isSelected(Coordinate coordinate);

    // drawing functions
    void drawState();
    void setWindowSize();
    void highlightCells();
    void drawCurrentPlayer();

    void showGameOver();

private slots:
    void handleBackgroundAndHighlightedFields();
    void handlePieceClick();

};

#endif // MAINWINDOW_H
