#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMenuBar>
#include <QAction>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QDebug>

class Dialog : public QDialog
{
    Q_OBJECT

public:
     Dialog();
    ~Dialog();
    void createMenu();
    void createHorizontalGroupBox();
    void createGridBox();
    void createFormBox();
    void printMessage();

private:

    enum {NumGridRows = 3, NumButtons = 4};

    //Menus:
    QMenuBar * menubar ;
    QMenu * fileMenu;
    QMenu * testMenu;
    QAction * exitAction;
    //QAction * testAction;


    QDialogButtonBox * buttonBox;

    //GroupBoxs:
    QGroupBox * horizontalGroupBox ;
    QGroupBox * gridGroupBox;
    QGroupBox * formGroupBox;

    //Widgets dans les GroupBoxs:
    QPushButton * buttons[NumButtons];
    QLineEdit * lineEdit[NumGridRows];
    QLabel * labels[NumGridRows];
    QTextEdit * smallEditor;
    QTextEdit * bigEditor;
};

#endif // DIALOG_H
