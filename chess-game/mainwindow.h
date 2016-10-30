#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>


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

    QPushButton **Board;
    QPushButton **BackgroundBoard;
    QLabel *TopLabels, *RightLabels, *BottomLabels, *LeftLabels;

    void setWindowSize();
    void createBoard();
    void createBackgroundBoard();
    void createLabels();

    QString getIdxName(int row,int col);

private slots:
    void handleBackgroundClick();
    void handlePieceClick();

};

#endif // MAINWINDOW_H
