#include "gameoptionswindow.h"
#include "ui_gameoptionswindow.h"

#include <QSignalMapper>
#include <random>
#include <time.h>

#include "uihelperfunc.h"

extern TGameType GameOptionsWindow::SelectedGameType;
extern std::string GameOptionsWindow::Player1Name;
extern std::string GameOptionsWindow::Player2Name;
extern Color GameOptionsWindow::SelectedColor;


GameOptionsWindow::GameOptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOptionsWindow)
{
    ui->setupUi(this);
    setStyleSheet(UIHelperFunc::getFormBackgroundStyleSheet());

    srand(time(NULL));

    SelectedGameType = gtNotSelected;
    isSelectedGameType = false;
    isSelectedColor = false;

    initUi();
}

GameOptionsWindow::~GameOptionsWindow() {
    delete ui;
}

/**
 * @brief GameOptionsWindow::initUi
 *
 * Initializes signals, slots and ui components.
 */
void GameOptionsWindow::initUi() {
    // Game Type
    connect(ui->radioButton_gameType_playerVsCPU, SIGNAL(clicked()), this,
            SLOT(on_radioButton_gameType_clicked()));
    connect(ui->radioButton_gameType_playerVsPlayer, SIGNAL(clicked()), this,
            SLOT(on_radioButton_gameType_clicked()));
    // Color
    connect(ui->radioButton_color_white, SIGNAL(clicked()), this,
            SLOT(on_radioButton_color_clicked()));
    connect(ui->radioButton_color_black, SIGNAL(clicked()), this,
            SLOT(on_radioButton_color_clicked()));
    connect(ui->radioButton_color_random, SIGNAL(clicked()), this,
            SLOT(on_radioButton_color_clicked()));

    ui->buttonBox->buttons().at(0)->setEnabled(false);

    ui->lineEdit_firstPlayer->setEnabled(false);
    ui->lineEdit_secondPlayer->setEnabled(false);
}

/**
 * @brief GameOptionsWindow::getSelectedGameType
 * @return Returns the selected game type.
 */
TGameType GameOptionsWindow::getSelectedGameType() {
    return SelectedGameType;
}

/**
 * @brief GameOptionsWindow::getSelectedColor
 * @return Returns the selected color of the first player.
 */
Color GameOptionsWindow::getSelectedColor() {
    return SelectedColor;
}

/**
 * @brief GameOptionsWindow::on_radioButton_gameType_clicked
 *
 * Event trigered when a button in the game type radio group is clicked.
 *
 * This method enables/disables appropriate fields and stores the current selected game type.
 */
void GameOptionsWindow::on_radioButton_gameType_clicked() {
    Player1Name = ui->lineEdit_firstPlayer->text().toStdString();

    if(ui->radioButton_gameType_playerVsCPU->isChecked()) {
        isSelectedGameType = true;
        SelectedGameType = gtPlayerVsCPU;
        ui->lineEdit_firstPlayer->setEnabled(true);
        ui->lineEdit_secondPlayer->setEnabled(false);

        Player2Name = "CPU";
    } else if(ui->radioButton_gameType_playerVsPlayer->isChecked()) {
        isSelectedGameType = true;
        SelectedGameType = gtPlayerVsPlayer;
        ui->lineEdit_firstPlayer->setEnabled(true);
        ui->lineEdit_secondPlayer->setEnabled(true);

        Player2Name = ui->lineEdit_secondPlayer->text().toStdString();
    }

    enableOkButton();
}

/**
 * @brief GameOptionsWindow::on_radioButton_color_clicked
 *
 * Event trigered when a button in the color radio group is clicked.
 *
 * This method enables/disables appropriate fields and stores the current selected color of first player.
 */
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

/**
 * @brief GameOptionsWindow::enableOkButton
 *
 * Enables the OK button if all fields are validly filled.
 * Disables the OK button otherwise.
 */
void GameOptionsWindow::enableOkButton() {
    Player1Name = ui->lineEdit_firstPlayer->text().toStdString();
    if(SelectedGameType==gtPlayerVsPlayer) {
        Player2Name = ui->lineEdit_secondPlayer->text().toStdString();
    } else {
        Player2Name = "CPU";
    }

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

/**
 * @brief GameOptionsWindow::on_lineEdit_firstPlayer_textChanged
 *
 * Fires event to check if the field is filled.
 */
void GameOptionsWindow::on_lineEdit_firstPlayer_textChanged(const QString&) {
    enableOkButton();
}

/**
 * @brief GameOptionsWindow::on_lineEdit_secondPlayer_textChanged
 *
 * Fires event to check if the field is filled.
 */
void GameOptionsWindow::on_lineEdit_secondPlayer_textChanged(const QString&) {
    enableOkButton();
}

/**
 * @brief GameOptionsWindow::getFirstPlayerName
 * @return Returns the name of the first player.
 */
std::string GameOptionsWindow::getFirstPlayerName() {
    return Player1Name;
}

/**
 * @brief GameOptionsWindow::getSecondPlayerName
 * @return Returns the name of the second player.
 */
std::string GameOptionsWindow::getSecondPlayerName() {
    return Player2Name;
}
