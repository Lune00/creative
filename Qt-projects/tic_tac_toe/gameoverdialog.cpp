#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"


gameOverDialog::gameOverDialog(QWidget *parent, QString message, bool hideNextRoundButton) :
    QDialog(parent),
    ui(new Ui::gameOverDialog)
{
    ui->setupUi(this);
    ui->nameWinner->setText(message);

    connect(ui->playagain,&QPushButton::clicked,this,&gameOverDialog::on_playagain_clicked);
    connect(ui->exit,&QPushButton::clicked,this,&gameOverDialog::on_exit_clicked);
    connect(ui->newGame,&QPushButton::clicked,this,&gameOverDialog::on_newGame_clicked);

    //If hideNextRoundButton : disable this button (gameOver option when Round_ = numberOfRounds):
    ui->playagain->setVisible(hideNextRoundButton);
}

gameOverDialog::~gameOverDialog()
{
    delete ui;
}

void gameOverDialog::on_playagain_clicked()
{
    done(1);
}


void gameOverDialog::on_newGame_clicked()
{
   done(2);
}

void gameOverDialog::on_exit_clicked()
{
    done(3);
}
