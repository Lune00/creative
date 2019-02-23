#ifndef GENOMEBANK_H
#define GENOMEBANK_H
#include<QAbstractTableModel>
#include<QModelIndex>
#include<QList>
#include<QString>

class Genome;

//On affiche le nom du genome (ie nom espece) / nbre de traits ds le genome
struct GenomeEntry
{
    QString name;
    int nbTraits;
    Genome* genome;

    //tmp
    bool operator==(const GenomeEntry& other) const{
        return name == other.name && genome == other.genome;
    }
};

class GenomeBank : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GenomeBank(QWidget *parent = nullptr);

    //Implementation des fonctions la classe Abstraite:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex& index) override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index)const override;


signals:

public slots:
private:
    QList<GenomeEntry> entries;

};

#endif // GENOMEBANK_H
