#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDialog>
#include<QTextEdit>
#include<QLineEdit>
#include <QPushButton>
#include <QLabel>

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    AddDialog(QWidget* parent = 0);
    //Entre le nom du genome
    QLineEdit* nameGenome_;
    //Entre un texte de commentaire pour l'utilisateur
    QTextEdit* commentsGenome_;
private:
    QLabel *nameLabel_;
    QLabel *commentLabel_;
    QPushButton* okButton_;
    QPushButton* cancelButton_;
};

#endif // ADDDIALOG_H
