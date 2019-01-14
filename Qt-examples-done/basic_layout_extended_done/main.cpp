#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    //Afficher la valeur de retour du dialog et l'afficher dans le terminal:
    //return a.exec();
    return w.exec();
}
