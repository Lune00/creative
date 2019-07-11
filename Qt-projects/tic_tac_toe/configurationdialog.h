#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <settings.h>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString player1Name READ
               player1Name WRITE
               setPlayer1Name)
    Q_PROPERTY(QString player2Name READ
               player2Name WRITE
               setPlayer2Name)

    enum NumberOfRounds{ One = 1, Three =3 , Five = 5};

public:
    explicit ConfigurationDialog(QWidget *parent = 0);
    ~ConfigurationDialog();

    void setPlayer1Name(const QString&);
    void setPlayer2Name(const QString&);
    QString player1Name() const;
    QString player2Name() const;
    int numberOfRounds() const ;
    unsigned int boardSize() const { return boardSize_;}

public slots:
    void updateBoardSizeSpinBox();
    void updateOkButtonState();

private:
    void setupNombreRounds();
    void setupGameType();
    Ui::ConfigurationDialog *ui;
    unsigned int boardSize_;
};

#endif // CONFIGURATIONDIALOG_H
