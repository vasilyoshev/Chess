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
    int offsetLeft;
    CellButton **Board;
    QPushButton **BackgroundBoard;
    QLabel *TopLabels, *RightLabels, *BottomLabels, *LeftLabels;
    vector<Coordinate> selectedCells;
    Coordinate *selectedPieceCoordinate;

    Controller controller;


    void drawState();
    void setWindowSize();
    void createBoard();
    void createBackgroundBoard();
    void createLabels();
    void initBackgroundBoardColor();
    QString getPieceFileName(Piece *p);
    bool isSelected(Coordinate coordinate);

private slots:
    void handleBackgroundClick();
    void handlePieceClick();

};

#endif // MAINWINDOW_H
