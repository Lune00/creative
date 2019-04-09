#include "notepad.h"
#include "ui_notepad.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent), ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionExit_triggered()
{
   QApplication::exit();
}

void Notepad::on_actionNew_triggered()
{
    currentfile = "";
    ui->textEdit->setText("");
}

void Notepad::on_actionopenFile_triggered()
{
    //Open a dialog box allowing to select a file:
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    //Stocke le fichier comme parametre
    QFile file(fileName);
    currentfile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","File not opened.");
        return;
    }
    //Cree un stream a partir du file
    QTextStream in(&file);
    //Recopie et saisie du texte dans text
    QString text = in.readAll();
    //On l'affiche dans le widget textEdit
    ui->textEdit->setText(text);
    file.close();
}
