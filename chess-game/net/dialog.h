#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "fortuneserver.h"

class QLabel;
class QPushButton;

class Dialog : public QWidget
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    FortuneServer server;
};

#endif
