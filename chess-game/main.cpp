#include "mainwindow.h"
#include <QApplication>
#include "net/dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // shows game menu
    //MainWindow w;
    //w.show();

    // shows server dialog
    Dialog dialog;
    dialog.show();

    return a.exec();
}
