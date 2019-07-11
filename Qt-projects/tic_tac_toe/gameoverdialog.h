#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class gameOverDialog;
}

class gameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverDialog(QWidget *parent = 0, QString message = "", bool hideNextRoundButton = true);
    ~gameOverDialog();
    bool playAgain() const { return playAgain_;}
    bool exit() const { return exit_;}

private slots:
    void on_playagain_clicked();

    void on_exit_clicked();

    void on_newGame_clicked();

private:
    Ui::gameOverDialog *ui;
    bool playAgain_;
    bool exit_;
};

#endif // GAMEOVERDIALOG_H
