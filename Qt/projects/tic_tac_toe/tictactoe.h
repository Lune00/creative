#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>

class QPushButton;


class TicTacToe : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Player)
    Q_PROPERTY(Player currentPlayer_ READ currentPlayer
               WRITE setCurrentPlayer
               NOTIFY currentPlayerChanged)
public:

    enum Player{
        Invalid, Player1, Player2, Draw
    };

    TicTacToe(QWidget *parent = 0);
    ~TicTacToe();

    void initNewGame(Player p = Player1);
    Player currentPlayer() const { return currentPlayer_;}
    void setCurrentPlayer(Player p) ;

    //Wining conditions:
    Player checkWinCondition();
    bool checkRows();
    bool checkCols();
    bool checkDiags();
    bool checkDraw();

signals:
    void currentPlayerChanged(Player p);
    void gameOver(TicTacToe::Player);

public slots:
    void handleButtonClick();

private:
    void setupBoard();

    QList<QPushButton*> Board_;
    Player currentPlayer_;
};

#endif // TICTACTOE_H
