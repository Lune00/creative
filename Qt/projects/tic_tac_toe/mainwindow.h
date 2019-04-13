#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tictactoe.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetNamesScores();
    void resetBoard(TicTacToe::Player = TicTacToe::Player1);
public slots:
    //Reset names and scores
    void startNewGame();
    //Continue with names and scores
    void startNewRound(TicTacToe::Player);
    void handleGameOver(TicTacToe::Player);

private slots:
    void updateNameLabels();

private:
    Ui::MainWindow *ui;
    int numberOfRounds_;
    int Round_;
    void updateStatusBar();
    //Player scores:
    int nRoundsWonP1_;
    int nRoundsWonP2_;

    QString gameOverMessage(TicTacToe::Player);

};

#endif // MAINWINDOW_H
