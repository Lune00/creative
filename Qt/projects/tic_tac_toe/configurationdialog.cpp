#include "configurationdialog.h"
#include "ui_configurationdialog.h"
#include <QPushButton>
#include <QtDebug>
#include <QComboBox>

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    setupNombreRounds();
    setupGameType();
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

void ConfigurationDialog::setupGameType(){
    ui->gameType->addItem(settings::enumToString(settings::typeOfBoard::standard));
    ui->gameType->addItem(settings::enumToString(settings::typeOfBoard::ultimate));
}

int ConfigurationDialog::numberOfRounds() const {
    QString choice = ui->numberRounds->currentText() ;
    bool ok = false;
    int nrounds = choice.toInt(&ok);
    if (ok) return nrounds;
    else return 1 ;
}

void ConfigurationDialog::updateBoardSizeSpinBox(){
    settings::typeOfBoard t = settings::stringToEnum(ui->gameType->currentText());
    bool ultimateSelected = (t == settings::typeOfBoard::ultimate);
    if (ultimateSelected){
        ui->sizeBoard->setValue(3);
        ui->sizeBoard->setDisabled(true);
    }
    else ui->sizeBoard->setDisabled(false);
    return ;
}

void ConfigurationDialog::updateOkButtonState(){

    //qDebug()<<"updateOkButtonState";
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
