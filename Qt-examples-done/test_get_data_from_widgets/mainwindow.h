#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

class GetDataUser;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
     MainWindow(GetDataUser&);
     void createModifySpace();
     void createReadSpace();
    ~MainWindow();

public slots:
     void updateText();
     void myEdit();

private:

     //Deux boites: une où on modifie les donnees, l'autre juste lecture
     QGroupBox * modifyspace ;
     QGroupBox * readspace ;


    //LineEdit qui permet l' interaction avec l'utilisateur
    QLineEdit * lineEdit;
    //LineEdit qui affiche le texte de GetDataUser
    QLineEdit * lineEditUser;
    QPushButton * button;
    GetDataUser * user;
};

#endif // MAINWINDOW_H
