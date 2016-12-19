#include "gameoptionswindow.h"
#include "ui_gameoptionswindow.h"

#include <QSignalMapper>
#include <random>
#include <time.h>

#include "uihelperfunc.h"

GameOptionsWindow::GameOptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOptionsWindow)
{
    ui->setupUi(this);
    setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());


    srand(time(NULL));

    SelectedGameType = gtNone;
    SelectedColor = (rand()%2==0 ? cWhite : cBlack);
    isSelectedGameType = false;
    isSelectedColor = false;

    initUi();
}

GameOptionsWindow::~GameOptionsWindow() {
    delete ui;
}

void GameOptionsWindow::initUi() {
    // Game Type
    connect(ui->radioButton_gameType_playerVsCPU,SIGNAL(clicked()),this,
            SLOT(on_radioButton_gameType_clicked()));
    connect(ui->radioButton_gameType_playerVsPlayer,SIGNAL(clicked()),this,
            SLOT(on_radioButton_gameType_clicked()));
    // Color
    connect(ui->radioButton_color_white,SIGNAL(clicked()),this,
            SLOT(on_radioButton_color_clicked()));
    connect(ui->radioButton_color_black,SIGNAL(clicked()),this,
            SLOT(on_radioButton_color_clicked()));
    connect(ui->radioButton_color_random,SIGNAL(clicked()),this,
            SLOT(on_radioButton_color_clicked()));

    ui->buttonBox->buttons().at(0)->setEnabled(false);

    ui->lineEdit_firstPlayer->setEnabled(false);
    ui->lineEdit_secondPlayer->setEnabled(false);


    /*QSignalMapper* mapper = new QSignalMapper(this);
    connect(ui->lineEdit_firstPlayer, SIGNAL(textChanged(QString)), mapper, SLOT(map()));
    connect(ui->lineEdit_secondPlayer, SIGNAL(textChanged(QString)), mapper, SLOT(map()));
    mapper->setMapping(ui->lineEdit_firstPlayer, "");
    mapper->setMapping(ui->lineEdit_secondPlayer, "");

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(on_lineEdit_textChanged(QString)));

    delete mapper;*/
}

TGameType GameOptionsWindow::getSelectedGameType() const {
    return SelectedGameType;
}

Color GameOptionsWindow::getSelectedColor() const {
    return SelectedColor;
}

void GameOptionsWindow::on_radioButton_gameType_clicked() {
    if(ui->radioButton_gameType_playerVsCPU->isChecked()) {
        isSelectedGameType = true;
        SelectedGameType = gtPlayerVsCPU;
        ui->lineEdit_firstPlayer->setEnabled(true);
        ui->lineEdit_secondPlayer->setEnabled(false);
    } else if(ui->radioButton_gameType_playerVsPlayer->isChecked()) {
        isSelectedGameType = true;
        SelectedGameType = gtPlayerVsPlayer;
        ui->lineEdit_firstPlayer->setEnabled(true);
        ui->lineEdit_secondPlayer->setEnabled(true);
    }

    enableOkButton();
}

void GameOptionsWindow::on_radioButton_color_clicked() {
    if(ui->radioButton_color_white->isChecked()) {
        isSelectedColor = true;
        SelectedColor = cWhite;
    } else if(ui->radioButton_color_black->isChecked()) {
        isSelectedColor = true;
        SelectedColor = cBlack;
    } else if(ui->radioButton_color_random->isChecked()) {
        isSelectedColor = true;
        SelectedColor = (rand()%2==0 ? cWhite : cBlack);
    }

    enableOkButton();
}

void GameOptionsWindow::enableOkButton() {
    bool filledNames = (!ui->lineEdit_firstPlayer->isEnabled() ||
                        (ui->lineEdit_firstPlayer->isEnabled() && ui->lineEdit_firstPlayer->text().size()!=0)) &&
            (!ui->lineEdit_secondPlayer->isEnabled() ||
             (ui->lineEdit_secondPlayer->isEnabled() && ui->lineEdit_secondPlayer->text().size()!=0));

    if(isSelectedGameType && isSelectedColor && filledNames) {
        ui->buttonBox->buttons().at(0)->setEnabled(true);
    } else {
        ui->buttonBox->buttons().at(0)->setEnabled(false);
    }
}


void GameOptionsWindow::on_lineEdit_firstPlayer_textChanged(const QString&) {
    enableOkButton();
}

void GameOptionsWindow::on_lineEdit_secondPlayer_textChanged(const QString&) {
    enableOkButton();
}

QString GameOptionsWindow::getFirstPlayerName() const {
    if(ui->lineEdit_firstPlayer->isEnabled()) {
        return ui->lineEdit_firstPlayer->text();
    } else {
        return QString("");
    }
}

QString GameOptionsWindow::getSecondPlayerName() const {
    if(ui->lineEdit_secondPlayer->isEnabled()) {
        return ui->lineEdit_secondPlayer->text();
    } else {
        return QString("CPU");
    }
}
