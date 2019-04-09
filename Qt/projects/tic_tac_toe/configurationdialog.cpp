#include "configurationdialog.h"
#include "ui_configurationdialog.h"
#include <QPushButton>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    setupNombreRounds();
    updateOkButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::setupNombreRounds(){

    ui->numberRounds->addItem(QString::number(NumberOfRounds::One) );
    ui->numberRounds->addItem(QString::number(NumberOfRounds::Three));
    ui->numberRounds->addItem(QString::number(NumberOfRounds::Five) );

}

int ConfigurationDialog::numberOfRounds() const {
    QString choice = ui->numberRounds->currentText() ;
    bool ok = false;
    int nrounds = choice.toInt(&ok);
    if (ok) return nrounds;
    else return 1 ;
}

void ConfigurationDialog::updateOkButtonState(){

    bool pl1NameEmpty = ui->player1Name->text().isEmpty();
    bool pl2NameEmpty = ui->player2Name->text().isEmpty();
    QPushButton* okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDisabled( pl1NameEmpty || pl2NameEmpty);

}

void ConfigurationDialog::setPlayer1Name(const QString& name){
    ui->player1Name->setText(name);
}

void ConfigurationDialog::setPlayer2Name(const QString& name){
    ui->player2Name->setText(name);
}
QString ConfigurationDialog::player1Name() const { return ui->player1Name->text();}
QString ConfigurationDialog::player2Name() const { return ui->player2Name->text();}
