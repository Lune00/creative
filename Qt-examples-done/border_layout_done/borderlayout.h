#ifndef BORDERLAYOUT_H
#define BORDERLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QList>
#include <QSize>
#include <QRect>


//TODO: encore deux fonctions a implementer : setGeometry et expandingDirections
//Comprendre margin et spacing en faisant un petit projet test dédié ou a la fin
//de celui-là. Je veux pouvoir bien maitriser disposition/taille widget et rescale.

//borderLayout herite de QLayout qui est une classe abstraite.
//Pour pouvoir l'instancier il est nécessaire d'implémenter
//toutes ses fonctions virtuelles pures: addItem,count,itemAt,takeAt
//pour eviter les erreurs on utilise le mot clef ovveride dans la declaration
//de ces fonctions afin d'etre sur qu'on les overwrite et non overload! (ce qui
//dans ce cas renderait abstrait la classe borderLayout et donc inanstantiable)

class borderLayout : public QLayout
{

public:

    enum Position{West,North,South,East,Center} ;

    //Premier constructeur:
    borderLayout(QWidget* parent,int margin = 0, int spacing = 0);
    //Deuxiement constructeur:
    //borderLayout(int spacing = -1);
    borderLayout(int margin = -1);

    //Les classes de Layout qui heritent de QLayout (comme QBoxLayout,QGridLayout etc...) gerent automatiquement la disposition etc, on a seulement besoin de faire appel a addWidget. Ici on developpe une Layout personalisée donc on doit organiser nous meme le layout. Pour cela on doit manipuler des Item (ce sont les objets manipulés par Layout qui contiennent les widgets)

    //Ajoute un widget au layout en le wrappand dans un item (appelle add)
    void addWidget(QWidget* widget,Position position);
    //Ajoute un item au layout (appelle add directement)

    void addItem(QLayoutItem* Item) override;
    //C++: override : assure que la fonction est virtuelle et que la définition
    //surcharge une fonction virtuelle de la classe mère (ici QLayout), hygiene.

    //Ajoute un item au Layout (ajoute a une QList, un conteneur d'Items)
    void add(QLayoutItem* Item,Position position);

    int count() const override;
    QLayoutItem * itemAt(int index) const override;
    QLayoutItem * takeAt(int index) override;

    //QLayout herite de QLayoutItem, qui possede cette fonction virtuelle pure
    QSize sizeHint() const override;
    QSize minimumSize() const override;


    void setGeometry(const QRect&) override;
    Qt::Orientations expandingDirections() const override;

    ~borderLayout();

private:

    struct ItemWrapper{
      ItemWrapper(QLayoutItem * i, Position p){
          item = i;
          position = p;
      }

      QLayoutItem * item ;
      Position position;
    };

    //Permet de définir si les widgets doivent avoir leur taille minimum (MinimumSize definie par l'utilisateur), ou la taille recommandée (SizeHint, valeur constante donnée par defaut)
    enum SizeType { MinimumSize, SizeHint };

    //Donne la taille totale des widgets dans le layout:(pas encore bien pigé)
    QSize calculateSize(SizeType sizeType) const;


    QList<ItemWrapper *> list;
};

#endif // BORDERLAYOUT_H
