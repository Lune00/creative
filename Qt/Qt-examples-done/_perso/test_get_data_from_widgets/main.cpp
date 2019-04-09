#include "mainwindow.h"
#include "getdatauser.h"
#include <QApplication>

//On cree une layout avec differents widgets
//On cree un objet qui recupere dans ses données entrees par l'utilisatuer sur les differents widgets (lineEdit, boutton, spinbox etc...)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GetDataUser user("Jean");

    MainWindow w(user);
    w.show();

    return a.exec();
}
