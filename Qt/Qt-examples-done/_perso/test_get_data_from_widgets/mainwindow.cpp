#include "mainwindow.h"
#include "getdatauser.h"
#include <QBoxLayout>
#include <QDebug>
#include <QFormLayout>
#include <QLabel>

MainWindow::MainWindow(GetDataUser& u)
{

    //Interface avec l'objet GetDataUser:
    user = &u ;

    //Creation des widgets:
    createModifySpace();
    createReadSpace();

    //Building layout:

    QLayout * mainlayout = new QVBoxLayout;

    mainlayout->addWidget(modifyspace);
    mainlayout->addWidget(readspace);

    setLayout(mainlayout);

}

MainWindow::~MainWindow()
{
    QString line = lineEdit->text();
    qDebug()<<"Destructeur "<<line;
}

//SLOTS:

//Valide le nouveau texte en appuyant sur Entree, repasse en mode lecture
void MainWindow::myEdit()
{
    lineEdit->clear();
    lineEdit->setReadOnly(false);
}

//On met a jour le text modifié et on met a jour le texte de getDataUser
void MainWindow::updateText()
{
    lineEdit->setReadOnly(true);
    user->setText(lineEdit->text());
    lineEditUser->setText(user->getText());
}



//QGroupBox: organisation du layout principal

void MainWindow::createModifySpace()
{
    modifyspace = new QGroupBox("Espace d'interaction");

    //Widgets: entree texte et bouton modifier
    lineEdit = new QLineEdit(user->getText());
    lineEdit->setReadOnly(true);
    button = new QPushButton("Modifier");

    //Connections:
    QObject::connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(updateText()));
    QObject::connect(button,&QPushButton::clicked,this,&MainWindow::myEdit);

    //Layout:
    QHBoxLayout * layout = new QHBoxLayout ;

    //Test sur les tailles min et Hint:
    //button->setMinimumSize(QSize(200,200));
    //qDebug()<<"sizeHint button ="<<button->sizeHint();
    //qDebug()<<"size button ="<<button->size();

    layout->addWidget(lineEdit);
    layout->addWidget(button);
    modifyspace->setLayout(layout);
}

void MainWindow::createReadSpace()
{

    readspace = new QGroupBox("Donnees membres de l'objet") ;
    lineEditUser = new QLineEdit(user->getText());
    lineEditUser->setReadOnly(true);

    QFormLayout * layout = new QFormLayout ;
    QLabel * champ = new QLabel("Nom: ");
    layout->addRow(champ, lineEditUser);
    layout->setFormAlignment(Qt::AlignLeft);
    readspace->setLayout(layout);
}
