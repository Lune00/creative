#include "genomewidget.h"
#include "genomebank.h"
#include "adddialog.h"
#include <QHeaderView>
#include <QTableView>
#include <QMessageBox>
#include <QStringList>

GenomeWidget::GenomeWidget(QWidget* parent): QWidget (parent)
{
    genomeBank_ = new GenomeBank(this);
    setup();
}

void GenomeWidget::setup()
{
    setup_view();
    qDebug()<<"call setup_view()";
}

//Le Widget ne s'affiche pas!!!! ni les headers .... MMMmmm....
void GenomeWidget::setup_view()
{
    tableView_ = new QTableView;

    //Connecte a QAbstractModel (base de données)
    tableView_->setModel(genomeBank_);

    //On selection les données vues par ligne (la ligne entiere)
    tableView_->setSelectionBehavior(QAbstractItemView::SelectRows);

    //La derniere section prend la place restante (false par defaut)
    tableView_->horizontalHeader()->setStretchLastSection(true);

    //Masque les headers horizontaux (vues a double entree)
    tableView_->verticalHeader()->hide();

    //Donne les regles d'edition des items representees par la tableView
    //Par exemple si on doubleclick sur un item pour l'editer...
    //TODO: pour le moment je mets noEdit mais apres on pourra editer
    //en double-clickant
    tableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Donne comportement de selection possible:
    //Juste un click-> 1 item, si Shift enfoncé on peut selectionner
    //plusieurs items contigus, si Cmd plusieurs pas contigus etc...
    //Ici (pour le moment) on veut SingleSlection, un seul selectionné a la fois
    tableView_->setSelectionMode(QAbstractItemView::SingleSelection);

    //Active l'ordonancement par colonne (pour ranger par nom une colonne par ex)
    tableView_->setSortingEnabled(true);

    //Connection:but? Ici cas particulier:
    //le signal de QItemSelectionModel selectionChanged() est connecté au signal
    //de GenomeWidget de selectionChanged()
    //On y reviendra. L'explication arrive dans mainWindow
    //Necessaire pour les actions "Edit Entry" et "Remove Entry"
    //dans le menu de mainWindow
    connect(tableView_->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &GenomeWidget::selectionChanged);

    //tableView_->show();
}

//Slot connecté a MainWindow "Ajouter un genome" action. La fonction cree un objet une QDialog très simple qui demande juste le nom du génome a ajouter
//Appel une QDialog AddDialog
void GenomeWidget::showAddEntryDialog()
{
    AddDialog addDialog;
    //Show la QDialog en mode modal (on peut plus interagir avec le reste du prog)
    // renvoie un int qui correspond au statut: bouton ok -> accepted(1)
    //                                          bouton cancel -> rejected(0)
    if(addDialog.exec()){
        QString name = addDialog.nameGenome_->text();
        QString comments = addDialog.commentsGenome_->toPlainText();
        //Ajoute une entree a la base de données:
        addEntry(name,comments);
    }
}

//On cree un nouveau Genome (avec new) et on lui assigne le nom et commentaire
//Doit également verifier que le nom n'existe pas deja

void GenomeWidget::addEntry(QString nameGenome, QString commentsGenome){
   //Verifier que le Genome n'existe pas encore dans le model
    if(!genomeBank_->contains(nameGenome))
    {
        qDebug()<<nameGenome<<" n'existe pas encore. On l'ajoute!";
        //Ajouter l'entree:
        //insere 1 ligne avant la ligne 0 (si 0 insérée devant les autres)

        qDebug()<<"Appel de insertRows...";
        genomeBank_->insertRows(0, 1, QModelIndex());
        qDebug()<<"Appel de insertRows...done";
        //renvoie l'index dans le model a la ligne 0, colonne 0, parent
        //ici ligne 0 (la ligne qu'on vient d'inserer)
        //colonne 0 pour la premiere donnee,
        //et pas de parent car c'est pas ds un QModelIndex() (arbre)
        QModelIndex index = genomeBank_->index(0, 0, QModelIndex());

        //Set la valeur du model colonne par colonne : colonne 1
        //Qt::EditRole pas encore tres clair...
        //Je passe nameGenome et commentsGenome (meme si commentsGenome) n'apparait pas
        //dans le model
        QStringList donees = { nameGenome, commentsGenome};

        qDebug()<<"Appel de setData";

        genomeBank_->setData(index, QVariant(donees), Qt::EditRole);
        //Pour l'instant qu'une colonne
        //Les commentaires doivent apparaitre ailleurs
    }
    else {
        //Sinon affiche une messageBox et l'entree est abandonnée.
        QMessageBox::information(this,"Nom de génome existant",tr("Le nom du génome \"%1\" existe déjà").arg(nameGenome));
    }


}

//Editer le nom du gene et les commentaires
//Verifier que si on change le nom il ne soit pas un nom deja existant
//Slot d'une action "Modifier Genome" ds barre d'outils et menu de QMainWindow
//TODO it later
void GenomeWidget::editEntry(){


}

//TODO it later
void GenomeWidget::removeEntry(){


}

//Input/Output
void GenomeWidget::readFromFile(const QString& filename){



}

void GenomeWidget::writeToFile(const QString& filename){



}
