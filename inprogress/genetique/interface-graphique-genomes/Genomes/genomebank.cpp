#include "genomebank.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGroupBox"
#include "genome.h"
#include <QDebug>

GenomeBank::GenomeBank(QWidget *parent) : QAbstractTableModel(parent)
{


}

//Fonctions virtuelles a réimplémenter:
//Nb lignes:
int GenomeBank::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return entries.size();
}

//Nb colonnes:
int GenomeBank::columnCount(const QModelIndex& parent) const{

    //Pas de waring si parent n'est pas utilisé
    Q_UNUSED(parent);
    return 2;
}

//Affiche les en-tetes de la table, ici Nom du genome et Nbre trait.
QVariant GenomeBank::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!= Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch(section) {
        case 0:
            return tr("Nom du Genome");
        case 1:
            return tr("Nombre de traits");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

// A REVOIR A LA FIN TOUT CE QUI EST Lié a data (comment ça marche en édition)


//Renvoie une donné membre du "model index" spécifié (ici nom, *Genome etc...)
//Accesseur
QVariant GenomeBank::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >= entries.size() || index.row() < 0)
        return QVariant();
    if(role == Qt::DisplayRole){
        const Genome* entry = entries.at(index.row());
        if(index.column() == 0)
            return entry->name();
        else if (index.column() == 1)
            return entry->nbTraits();
    }
    return QVariant();
}


//Pour editer la table: inserer une ligne (redefinie manuellement ici)

//(position,rows):

//Cette fonction est appelée avant que des données soient ajoutees au model, sinon les donnes ne seront pas affichées.

//Je pense que de maniere generale pour les Tree on peut inserer des lignes
//dans un ModelIndex du modele. Ici on ajoute apres ou avant mais jamais dedans
//car c'est pas un arbre mais une liste a plusieurs colonnes. Du coup on l'utilise pas.  Avec le constructeur l'index de QModelIndex() est invalide, comme il est invalide ca n'insere pas les nouvelles lignes dans le QModelIndex(). De toute maniere on insere ensuite manuellement dans notre QList entries apres. Ca bricole


//Pareil mais retire des lignes
bool GenomeBank::removeRows(int position, int rows, const QModelIndex& index)
{
    Q_UNUSED(index);
    //Indique aux views qu'on fait des changements
    beginInsertRows(QModelIndex(), position, position + rows -1);

    for(int row = 0 ; row < rows ; rows++)
    {
        entries.removeAt(position);
    }
    //fin des changements
    endInsertRows();
    return true;
}

//Les rows du model sont des images des positions ds QList Genomes
//Quand on ajoute une entree, on ajoute une ligne au model et un element a entries avec "insert"
bool GenomeBank::insertRows(int position, int rows, const QModelIndex& index)
{
    Q_UNUSED(index);
    //Indique aux views qu'on fait des changements
    beginInsertRows(QModelIndex(), position, position + rows -1);

    for(int row = 0 ; row < rows ; row++)
    {
        Genome* g = new Genome() ;
        entries.insert(position, g);
    }
    //fin des changements
    endInsertRows();
    return true;
}
//Insere des données dans la table, item par item et non ligne par ligne. Pour remplir une ligne setData() doit etre appelée autant de fois qu'il y'a de colonnes (ici 2 pour le moment). Elle etmit le signal dataChanged() pour dire aux vues de s'updater
//On modifie les valeurs de QModelIndex par value.

//Comment passer comments dans QVariant ici? on va passer les deux QString dans une QStringList qu'on metera dans un QVariant (car c'est une fonction override, je dois respecter la définition)
bool GenomeBank::setData(const QModelIndex& index, const QVariant& value,int role)
{
    QString name = value.toStringList().takeFirst();
    QString comments = value.toStringList().takeFirst();

    qDebug()<<"name: "<<name<<" comments: "<<comments;

    if(index.isValid() && role == Qt::EditRole){
        //la ligne row de l'index correspond a la position de l'entree
        //dans la QList entries
        int row = index.row();
        //On fait une copie du pointeur, on pointe sur le genome en memoire
        Genome* const entry = entries.value(row);
        //On modifie selon la colonne (quel attribut de l'entree est modifiee)
        if(index.column() == 0){
            entry->setname( name );
            entry->setcomments( comments );
        }
        //else if(index.column() == 1)
            //Ici c'est affiché, c'est pas connu a l'avance TODO
        else
            return false;

        //On remplace l'entree dans la QList avec la nouvelle entree
        //Pas besoin car c'est un pointeur, on modifie direct
        //l'objet pointé en passant par entry->
        //entries.replace(row,entry);

        //On emet un signal aux vues pour dire de s'updater
        //(index,index) met a jour entre index et index (lui et lui)
        //inclusive (pas toute la table)
        emit dataChanged(index,index, {role});
        return true;
    }
    return false;
}

//Renvoie le flag de l'item a l'index donné
//ici on dit que le TableModel peut etre edité
Qt::ItemFlags GenomeBank::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable ;
}

bool GenomeBank::contains(QString name){
    QList<Genome*>::ConstIterator it = entries.begin();
    while(it != entries.end()){
        if( (*it)->name() == name){
            return true;
        }
            it++;
    }
    return false;
}
