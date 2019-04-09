#include "dialog.h"
#include <QDebug>
#include <QBoxLayout>
#include <QPushButton>
#include <QString>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>

//Layout principal défini dans le constructeur
Dialog::Dialog()
{
    //On cree un layout vertical sur le widget Dialog:
    QVBoxLayout * mainLayout = new QVBoxLayout;

    //Construction des differents widgets du layout:
    createMenu();
    createHorizontalGroupBox();
    createGridBox();
    createFormBox();

    //Construction de la boite de dialogue bouttons:
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);

    //Qt4. syntax pour la connection:
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    //Qt5. syntax pour la connection: a utiliser de preference!
    connect(buttonBox,&QDialogButtonBox::helpRequested,this,&Dialog::printMessage);

    //On ajoute les widgets au Layout: l'ordre compte evidemment!
    mainLayout->setMenuBar(menubar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
     //On ajoute le dernier editeur de texte ici:
    bigEditor = new QTextEdit;
    mainLayout->addWidget(bigEditor);
    //Les boutons a la fin
    mainLayout->addWidget(buttonBox);


    //Assigne le Layout a Dialog (fenetre principale):
    setLayout(mainLayout);
    setWindowTitle("Les Layouts");

}

Dialog::~Dialog()
{

}

//Creer la bare de menu
void Dialog::createMenu()
{
    menubar = new QMenuBar ;
    fileMenu = new QMenu("Fichier",this);
    testMenu = new QMenu("&Fichier2",this);

    //qDebug()<<"native menubar:"<< menubar->isNativeMenuBar();

    //action = qmenu->addAction(text):
    //Cree une nouvelle action avec le texte text
    //addAction ajoute l'action text au qmenu (cree une entree dans QMenu)
    //et renvoie l'action. QMenu est le proprietaire de exitAction.

    exitAction = fileMenu->addAction("Fermer");

    //connect(qu'est ce qui envoit le signal (pointeur sur Widget),
    //        SIGNAL(le signal()),
    //        qu'est ce qui recoit le signal (pointeur sur Widget,ou App),
    //        SLOT(le slot, fonction a appeler())
    //        )
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(reject()));
    //connect(testAction,SIGNAL(triggered(bool)),this,SLOT(reject()));

    //On ajoute le QMenu a la barre QMenuBar
    menubar->addMenu(fileMenu);
    //menubar->addMenu(testMenu);
}

//Creer le GroupBox horizontal avec les NumButtons bouttons
void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox("Layout Horizontal");
    //A test: permet de dessiner le contour du frame alloué à GQroupBox
    horizontalGroupBox->setFlat(false);

    QHBoxLayout * layout = new QHBoxLayout;


    for(unsigned int i = 0 ; i < NumButtons ; i++)
    {
        buttons[i] = new QPushButton(QString("Bouton %1").arg(i + 1));
        layout->addWidget(buttons[i]);
    }

    horizontalGroupBox->setLayout(layout);
}

void Dialog::createGridBox()
{
    //1) On cree le widget containener : un QGroupBox
    gridGroupBox = new QGroupBox("Layout en grille");
    //2) On cree le layout en grille que l'on va installer dessus
    QGridLayout * layout = new QGridLayout ;
    //3) On ajoute les widgets au layout:
    for(unsigned int i=0;i<NumGridRows;i++)
    {
        labels[i] = new QLabel(QString("Ligne %1:").arg(i + 1));
        lineEdit[i] = new QLineEdit;
        layout->addWidget( labels[i], i + 1, 0);
        //layout->addWidget( lineEdit[i], i + 1, 1, Qt::AlignCenter);
        layout->addWidget( lineEdit[i], i + 1, 1);
    }

    smallEditor = new QTextEdit ;
    layout->addWidget(smallEditor, 0, 2, 4, 1);

    //Stretch factor: relatif, plus stretch est grand plus prend d'espace
    // par defaut egal a 0 (prend le minimum ou espace laissé par defaut
    layout->setColumnStretch(1,10);
    layout->setColumnStretch(2,20);
    // On peut également stretch les lignes (rows)
    // layout->setRowStretch(1,20);

    //4) On installe le layout sur le GroupBox
    gridGroupBox->setLayout(layout);
}

void Dialog::createFormBox()
{
    formGroupBox = new QGroupBox("Layout Formulaire") ;
    QFormLayout * layout = new QFormLayout ;
    layout->addRow("Nom:",new QLineEdit);
    //layout->addRow("S'il vous plait donnez votre adresse complète internationalement reconnue:",new QComboBox);
    layout->addRow("Adresse:",new QComboBox);
    layout->addRow("Âge:",new QSpinBox);

    formGroupBox->setLayout(layout);
}

//Fonction appelée lorsqu'on clique sur le bouton Help
void Dialog::printMessage()
{
    QMessageBox * message = new QMessageBox(this);
    message->setText("Vous avez demandé de l'aide.");

    //Petit test, ce n'est pas vraiment de la localisation a proprement dit
    //On verra ca plus tard dans un autre exercice
    message->setButtonText(QMessageBox::Ok,"D'accord");
    //On stocke le resultat dans ret
    int ret = message->exec();

    //Exemple de travail a partir du signal emis par MessageBox:
    switch(ret){
    case QMessageBox::Ok: qDebug()<<"De l'aide a été demandée";
        break;
    default:
        break;
    }
}

