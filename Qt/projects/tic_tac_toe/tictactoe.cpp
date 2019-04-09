#include "tictactoe.h"
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

TicTacToe::TicTacToe(QWidget *parent)
        : QWidget(parent)
{
    setupBoard();
    setCurrentPlayer(Player1);
}

TicTacToe::~TicTacToe()
{

}

void TicTacToe::setCurrentPlayer(Player p)
{
    if ( currentPlayer_ == p ){
        return ;
    }
    else{
        currentPlayer_ = p ;
        emit currentPlayerChanged(p);
    }
}


void TicTacToe::setupBoard()
{
    QGridLayout* gridLayout = new QGridLayout(this);
    //alternative: setLayout(gridLayout);
    for(int row = 0 ; row < 3 ; row++){
        for (int col = 0 ; col < 3 ; col++){
            QPushButton* button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

            //Debug
            // QString button_text = QString::number(row) + QString::number(col);
            // button->setText(button_text);
            button->setText(" ");

            gridLayout->addWidget(button,row,col);
            Board_.append(button);
            connect(button, &QPushButton::clicked,this,&TicTacToe::handleButtonClick);
        }
    }

}
void TicTacToe::initNewGame(Player p)
{
    for(int i=0; i!=9; i++) Board_.at(i)->setText(" ");
    if (p == Draw ) p = Player1;
    setCurrentPlayer(p);
}


void TicTacToe::handleButtonClick(){

    QPushButton* button =  qobject_cast<QPushButton*>(sender());

    if( button != NULL )
    {
        if( button->text() != " ")
            return ;
        else{
            button->setText(currentPlayer_ == Player1 ? "X" : "O");
            TicTacToe::Player winner = checkWinCondition();
        if(winner == Invalid){
                setCurrentPlayer(currentPlayer_ == Player1 ? Player2 : Player1 );
                return ;
            }
        else if (winner == Draw){
            emit gameOver(winner);
        }
        else{
            emit gameOver(winner);
        }
    }
    }
    else
    {
        return ;
    }
}

//Regarde 3 lignes, 3 colonnes et 2 diagonales du currentPlayer_
// TODO: add Draw conditions, all cases full
TicTacToe::Player TicTacToe::checkWinCondition(){

    if( checkRows() || checkCols() || checkDiags() )
        return currentPlayer();
    else if (checkDraw())
        return Draw;
    else
        return Invalid;
}

bool TicTacToe::checkRows(){
    QString p = (currentPlayer_ == Player1 ? "X" : "O");
    for(int row = 0 ; row != 3 ; row++){
        if ( Board_.at(row * 3 )->text() == p && Board_.at(row * 3 + 1)->text() == p && Board_.at(row*3 + 2)->text() == p){
            return true;
        }
    }
    return false;
}

bool TicTacToe::checkCols(){
    QString p = (currentPlayer_ == Player1 ? "X" : "O");
    for(int i = 0 ; i != 3 ; i++){
        if ( Board_.at(i)->text() == p && Board_.at(i + 3)->text() == p && Board_.at(i + 6)->text() == p){
            return true;
        }
    }
    return false;
}

bool TicTacToe::checkDiags(){
    QString p = (currentPlayer_ == Player1 ? "X" : "O");
    bool diag1 = (Board_.at(0)->text() == p && Board_.at(4)->text() == p && Board_.at(8)->text() == p);
    bool diag2 = (Board_.at(2)->text() == p && Board_.at(4)->text() == p && Board_.at(6)->text() == p);
    if( diag1 || diag2 )
        return true;
    else
        return false;
}

bool TicTacToe::checkDraw(){
    for(int i = 0 ; i != Board_.size() ; i++){
        if ( Board_.at(i)->text() == " ")
            return false;
    }
    return true;
}
