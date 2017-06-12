#include <QApplication>
#include "net/dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // shows server dialog
    Dialog dialog;
    dialog.show();

    return a.exec();
}
