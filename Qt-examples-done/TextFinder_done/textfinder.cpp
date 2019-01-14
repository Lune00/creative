#include "textfinder.h"
#include "ui_textfinder.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>

TextFinder::TextFinder(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TextFinder)
{
    ui->setupUi(this);
    loadTextFile();
}

TextFinder::~TextFinder()
{
    delete ui;
}

void TextFinder::loadTextFile()
{
    //Selectionne un fichier
    QFile inputFile(":/input.txt");
    //Ouverture fichier en mode lecture seule avec QIODevice
    inputFile.open(QIODevice::ReadOnly);
    //Envoyé dans un stream
    QTextStream in(&inputFile);
    //Lit le buffer et renvoie le contenu dans un QString
    QString line = in.readAll();
    //Pour debuger: outil natif qDebug (include QDebug)
    //qDebug() << line ;
    //Fermeture du fichier
    inputFile.close();
    //Assigne le champ de textEdit au texte du fichier chargé
    ui->textEdit->setPlainText(line);

    //Definit la couleur du highlight de l'expression que l'on cherche
    //par defaut ici il est gris:

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Highlight,QColor ("darkBlue"));
    p.setColor(QPalette::HighlightedText,QColor ("white"));
    ui->textEdit->setPalette(p);

}

void TextFinder::on_findButton_clicked()
{

    //Placer le curseur au debut du texte charge dans textEdit
    QTextCursor myCursor = ui->textEdit->textCursor();
    myCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
    ui->textEdit->setTextCursor(myCursor);

    //Get the expression to find within the text:
    QString searchedString = ui->lineEdit->text();

    //A expliciter: comment se comporte le curseur?
    //find: Finds the next occurrence of the string, searchedString,
    //using the given options. Returns true if searchedString was found
    //and changes the cursor to select the match; otherwise returns false.

    ui->textEdit->find(searchedString,QTextDocument::FindWholeWords);

    //Affiche la position du curseur:
    qDebug() << ui->textEdit->textCursor().position();
    //Affiche la position de l'anchor:
    //qDebug() << ui->textEdit->textCursor().anchor();

}

