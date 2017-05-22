#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "server.h"
#include <QPushButton>
#include <QLabel>

class Dialog : public QWidget
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    Server server;
};

#endif
