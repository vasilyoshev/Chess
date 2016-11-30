#ifndef GAMEOPTIONSWINDOW_H
#define GAMEOPTIONSWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QRadioButton>
#include "color.h"
#include "gametype.h"

namespace Ui {
class GameOptionsWindow;
}

class GameOptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameOptionsWindow(QWidget *parent = 0);
    ~GameOptionsWindow();

    TGameType getSelectedGameType() const;
    Color getSelectedColor() const;
    QString getFirstPlayerName() const;
    QString getSecondPlayerName() const;

private slots:
    void on_radioButton_gameType_clicked();
    void on_radioButton_color_clicked();

    void on_lineEdit_firstPlayer_textChanged(const QString &arg1);

    void on_lineEdit_secondPlayer_textChanged(const QString &arg1);

private:
    Ui::GameOptionsWindow *ui;

    TGameType SelectedGameType;
    Color SelectedColor;
    bool isSelectedGameType;
    bool isSelectedColor;

    void initUi();
    void enableOkButton();
};

#endif // GAMEOPTIONSWINDOW_H
