#ifndef GENOMEWIDGET_H
#define GENOMEWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>

//utilisateur <-> mainwindow <-> GenomeWidget (via Dialog): affichage /edition <-> GenomeBank (base de données) (prend en compte les editions et modifie la base de données, dit ce qui peut etre modifie ou non) <-> Genome (données a editer)


//Manipule la base de données (genomebank): ajout/retirer/edite
//,met en place le filtre de données, et l'affichage de la base

//Widget central de MainWindow

class GenomeBank;
class QTableView;

class GenomeWidget: public QWidget
{
    Q_OBJECT

public:

public slots:
    void showAddEntryDialog();
    void addEntry(QString name_genome, QString comments);

signals:
    void selectionChanged (const QItemSelection& selected);

private:
    GenomeWidget(QWidget* parent = 0);

    void setup();
    void setup_view();
    //void setup_proxyModel();

    GenomeBank* genomeBank_;
    QTableView* tableView_;
    //QSortFilterProxyModel *proxyModel_;

};

#endif // GENOMEWIDGET_H
