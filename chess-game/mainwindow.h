#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>

#include "controller.h"
#include "cellbutton.h"


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
    vector<Coordinate> selectedCells;
    Coordinate selectedPieceCoordinate;
    Controller controller;

    // initialization functions
    void createBoard();
    void createBackgroundBoard();
    void createLabels();
    void initBackgroundBoardColor();

    // help functions
    QString getPieceFileName(Piece *p);
    bool isSelected(Coordinate coordinate);
    QString getBackgroundStyleSheet(QString color);
    QString getBackgroundAndHoverStyleSheet(QString backgroundColor, QString hoverColor);

    // drawing functions
    void drawState();
    void setWindowSize();
    void markCells();
    void unmarkCells();
    void drawCurrentPlayer();

private slots:
    void handleBackgroundClick();
    void handlePieceClick();

};

#endif // MAINWINDOW_H
