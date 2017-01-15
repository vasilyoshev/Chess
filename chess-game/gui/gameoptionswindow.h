#ifndef GAMEOPTIONSWINDOW_H
#define GAMEOPTIONSWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QRadioButton>
#include <string>

#include "color.h"
#include "gametype.h"

namespace Ui {
class GameOptionsWindow;
}

/**
 * @brief The GameOptionsWindow class
 *
 * This class is used to show a dialog at the start of the application.
 *
 * This dialog helps to setup the game, like choosing the name of the players and choosing the game mode.
 */
class GameOptionsWindow : public QDialog {
    Q_OBJECT

public:

    explicit GameOptionsWindow(QWidget* parent = 0);
    ~GameOptionsWindow();

    static TGameType getSelectedGameType();
    static Color getSelectedColor();
    static std::string getFirstPlayerName();
    static std::string getSecondPlayerName();

private slots:
    void on_radioButton_gameType_clicked();
    void on_radioButton_color_clicked();
    void on_lineEdit_firstPlayer_textChanged(const QString &arg1);
    void on_lineEdit_secondPlayer_textChanged(const QString &arg1);

private:
    Ui::GameOptionsWindow* ui;

static std::string Player1Name;
static std::string Player2Name;
static TGameType SelectedGameType;
static Color SelectedColor;
bool isSelectedGameType;
bool isSelectedColor;

    void initUi();
    void enableOkButton();
};

#endif // GAMEOPTIONSWINDOW_H
