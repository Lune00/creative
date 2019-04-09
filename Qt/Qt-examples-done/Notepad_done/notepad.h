#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QString>
#include<iostream>

//Forward declaration, dire que cette classe existe ailleurs
//et pouvoir declarer un pointeur, cette classe Ui::Notepad
//est creee dans le fichier genere de c++ par QtDesigner
namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();

private slots:
    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_actionopenFile_triggered();

private:
    //Classe differente : herite de Ui_Notepad genere par QtDesigner
    Ui::Notepad *ui;
    QString currentfile;
};

#endif // NOTEPAD_H
