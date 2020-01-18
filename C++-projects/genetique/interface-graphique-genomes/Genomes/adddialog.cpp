#include "adddialog.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

AddDialog::AddDialog(QWidget* parent): QDialog (parent)
{
    //Labels:
    nameLabel_ = new QLabel("Nom du génome");
    commentLabel_  = new QLabel("Commentaires");
    //Boutons:
    okButton_ = new QPushButton("Ok");
    cancelButton_  = new QPushButton("Cancel");
    //Edit widgets:

    nameGenome_ = new QLineEdit;
    commentsGenome_ = new QTextEdit;

    //Layout pour les widgets d'edition:

    QGridLayout* gLayout = new QGridLayout;
    //augmente la taille de la colonne 1 par un facteur 2 (par rapport a la 0,
    //premiere colonne)
    gLayout->setColumnStretch(1,2);
    gLayout->addWidget(nameLabel_,0,0);
    gLayout->addWidget(nameGenome_,0,1);
    gLayout->addWidget(commentLabel_,1,0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(commentsGenome_,1,1, Qt::AlignTop) ;

    //Layout pour les boutons de la boite de dialogue
    QHBoxLayout *buttonLayout = new QHBoxLayout ;
    buttonLayout->addWidget(okButton_);
    buttonLayout->addWidget(cancelButton_);
    //Ajoute une layout au Grid layout (cool)
    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    //MainLayout: je vois pas l'interet....
    QVBoxLayout* mainLayout = new QVBoxLayout ;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    //Connections:
    connect(okButton_, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton_, &QAbstractButton::clicked, this, &QDialog::reject);

}
