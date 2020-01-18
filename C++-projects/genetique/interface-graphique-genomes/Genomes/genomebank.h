#ifndef GENOMEBANK_H
#define GENOMEBANK_H
#include<QAbstractTableModel>
#include<QModelIndex>
#include<QList>
#include<QString>

#include "genome.h"

//TableModel: notre modele(base) de données
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

    //Données:
    QList<Genome*> getGenomes() const { return entries ;}

    bool contains(QString name);

signals:

public slots:
private:
    QList<Genome*> entries;

};

#endif // GENOMEBANK_H
