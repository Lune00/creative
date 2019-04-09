#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configurationdialog.h"
#include "gameoverdialog.h"

#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setIconSize(QSize(20,20));
    ui->gameBoard->setEnabled(false);

    //Connects:
    connect(ui->actionNew_Game,&QAction::triggered,this,&MainWindow::startNewGame);
    connect(ui->actionQuit,&QAction::triggered,qApp,&QApplication::quit);
    //ui->gameBoard == tictactoe (Promoted in Qt Design)
    connect(ui->gameBoard,&TicTacToe::currentPlayerChanged,this,&MainWindow::updateNameLabels);
    connect(ui->gameBoard,&TicTacToe::gameOver,this,&MainWindow::handleGameOver);
    //Scores:
    nRoundsWonP1_ = 0 ;
    nRoundsWonP2_ = 0 ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNameLabels(){

    if (ui->gameBoard->currentPlayer() == TicTacToe::Player1){
        QFont f = ui->player1->font();
        f.setBold(true);
        ui->player1->setFont(f);
        f.setBold(false);
        ui->player2->setFont(f);
    }
    else{
        QFont f = ui->player2->font();
        f.setBold(true);
        ui->player2->setFont(f);
        f.setBold(false);
        ui->player1->setFont(f);
    }

}

void MainWindow::resetBoard(TicTacToe::Player winner){
    ui->gameBoard->initNewGame(winner);
    ui->gameBoard->setEnabled(true);
    return;
}

void MainWindow::updateStatusBar(){
    ui->statusbar->showMessage("Round :"+QString::number(Round_)+"/"+QString::number(numberOfRounds_));
}
void MainWindow::resetNamesScores(){

    //Scores:
    nRoundsWonP1_ = 0 ;
    nRoundsWonP2_ = 0 ;

    ui->statusbar->showMessage(" ");

    ConfigurationDialog dlg(this);
    if(dlg.exec() == QDialog::Rejected){
        return ;
    }
    //Names:
    ui->player1->setText(dlg.player1Name());
    ui->player2->setText(dlg.player2Name());
    updateNameLabels();

    //Rounds counter:
    numberOfRounds_ = dlg.numberOfRounds() ;
    Round_ = 1 ;
    updateStatusBar();

    return;
}

void MainWindow::startNewGame(){
    resetNamesScores();
    resetBoard();
    return ;
}

void MainWindow::startNewRound(TicTacToe::Player winner){
    Round_++;
    resetBoard(winner);
    updateStatusBar();
    return;
}


QString MainWindow::gameOverMessage(TicTacToe::Player winner){

    QString message;
    bool gameIsFinished = (Round_ ==  numberOfRounds_);
    bool draw = (nRoundsWonP1_ == nRoundsWonP2_);

    if(gameIsFinished){

        if(draw){

            message = QString("Game ended with a draw (%1 to %2)").arg(
                                    nRoundsWonP1_).arg(nRoundsWonP2_);
        }
        else{

            if(numberOfRounds_ == 1 ) {
                message = QString("%1 wins the game !").arg(winner ==
                                                            TicTacToe::Player1 ? ui->player1->text() :
                                                                                 ui->player2->text());
            }
            else{
                message = QString("%1 wins the game %2 to %3 !")
                                .arg(nRoundsWonP1_ > nRoundsWonP2_ ? ui->player1->text() :ui->player2->text())
                                .arg(nRoundsWonP1_ > nRoundsWonP2_ ? nRoundsWonP1_ : nRoundsWonP2_)
                                .arg(nRoundsWonP1_ > nRoundsWonP2_ ? nRoundsWonP2_ : nRoundsWonP1_);
            }
        }
    }
    //Next round
    else
    {
        if(winner == TicTacToe::Draw) message = "Game ended with a draw.";
        else{
            message = QString("%1 wins this round !").arg(winner ==
                                                          TicTacToe::Player1 ? ui->player1->text() :
                                                                               ui->player2->text());
        }
    }
    return message;
}

void MainWindow::handleGameOver(TicTacToe::Player winner){

    ui->gameBoard->setEnabled(false);
    bool gameIsFinished = (Round_ ==  numberOfRounds_);

    //Update scores:
    switch (winner) {
    case TicTacToe::Player1:
        nRoundsWonP1_++;
        break;
    case TicTacToe::Player2:
        nRoundsWonP2_++;
        break;
    case TicTacToe::Draw:
        break;
    case TicTacToe::Invalid:
        break;
    }

    QString message = gameOverMessage(winner);


    //What's next? Continue the game (with a new round), quit or start a new one -> get answer
    int answer ;

    if(gameIsFinished){
        gameOverDialog dlg(this,message,false);
        answer = dlg.exec();
    }
    else{
        gameOverDialog dlg(this,message);
        answer = dlg.exec();
    }

    switch (answer) {
    //New Round : Keep names and scores: winner plays first at next game
    case 1:
        startNewRound(winner);
        break;
        //Reset names and scores:
    case 2:
        startNewGame();
        break;
        //Quit:
    case 3:
        ui->actionQuit->trigger();
        break;
    default:
        return ;
    }
    return ;
}
