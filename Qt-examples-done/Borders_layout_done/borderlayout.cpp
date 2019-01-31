#include "borderlayout.h"
#include <QDebug>

borderLayout::borderLayout(QWidget* parent,int margin , int spacing )
        :QLayout(parent)
{
    setMargin(margin);
    setSpacing(spacing);
}

borderLayout::borderLayout(int margin )
{
    qDebug()<<"constructeur";
    //Appelle minimumSize()
    setSizeConstraint(QLayout::SetMinimumSize);
    setMargin(margin);
}


//takeAt renvoie un item (ici takeAt(0) renvoie l'item a l'index 0). Une fois retiré, les index sont remis a jour (l'item 1 devient 0 etc..)
//Si il n'y a plus d'item alors (i = takeat(0) ) est égale à 0 (c'est le comportement te takeAt), et -> while(false) . Ok

borderLayout::~borderLayout(){

    QLayoutItem * i;
    while((i = takeAt(0))){
        delete i;
    }

}

//Permet d'autoriser la layout a utiliser plus d'espace que sizeHint(). Une valeur de Qt::Horizontal dit que ca peut grandir que dans la direction horizontale, Qt::Vertical | Qt::Horizontal dit que ça peut augmenter l'espace dans les 2 directions

Qt::Orientations borderLayout::expandingDirections()const
{
    return Qt::Horizontal | Qt::Vertical;
}

void borderLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget),position);
}

//QLayoutItem est un type abstrait, il ne peut pas etre instancié (on peut avoir un pointeur vers une classe abstraite, on peut deferencer ses parties non abstraites)
void borderLayout::add(QLayoutItem* Item, Position position)
{
    //Ici je recupere un pointeur sur QWdigetItem child class de QLayoutItem
    //Normalement a partir de Item je ne peux plus acceder aux
    //methodes/attributs de QWidgetItem, mais QWidgetItem EST un QLayoutItem
    //test:
    // bool a = Item->isEmpty();
    list.append(new ItemWrapper(Item, position));
}

//Uniquement a l'West, on verra plus tard pourquoi j'imagine...
void borderLayout::addItem(QLayoutItem* Item)
{
    add(Item,West);
}

//Renvoie le nombre d'items dans la liste
int borderLayout::count() const
{
    return list.size();
}

//Renvoie l'Item index de la list
QLayoutItem * borderLayout::itemAt(int index) const
{
    ItemWrapper * iw = list.value(index);
    if(iw)
        return iw->item;
    else
        return 0;
}

//Retire un Item du layout et le renvoie
QLayoutItem * borderLayout::takeAt(int index)
{
    if( index >=0 && index < list.size()) {
        ItemWrapper * iw = list.takeAt(index);
        return iw->item;
    }
    else
        return 0;
}

//La fonction sert juste a calculer la taille minimale de la fenetre de l'application, en additionnant la taille minimum/ou recommandée (argument) de chaque widget. Cette fonction on s'en sert pas ici mais elle doit etre ecrite car elle est appelée dans sizeHint() qui est une fonction virtuelle de QLayout.

//Prend en argument un type de taille: Minimum ou SizeHint (minimum definie par user, ou recommandee)

//Fonction qui renvoie la taille recommandée pour l'application (ici notre fenetre)
//elle se base sur la taille totale min/recommandee (argument de sizeHint) de tous les widgets. Ok.


QSize borderLayout::minimumSize() const
{
    return calculateSize(SizeHint);
}

QSize borderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

//De la Doc:

//minimumSize: membre de QWidget. Cette propriété contient la taille minimum du Widget. Le widget ne peut pas avoir une taille inférieure a la taille minimumSize(). La taille du widget est forcée a etre égale a minimum size si la taille actuelle est plus petite (QSize(width,height).

//minimumSizeHint: membre de QWidget. Cette propriété contient la taille recommandée minimale pour le Widget, c'est une constante. QLayout ne changera pas la taille d'un widget si elle est plus petite que minimumSizeHint() SAUF si minimumSize() est manuellement reglee, dans ce cas minimumSizeHint sera ignorée.

//sizeHint: membre de QWidget. This property holds the recommended size for the widget. L'implementation par defaut renvoie une taille invalide s'il n'y a pas de layout pour le widget, sinon elle renvoie la taille recommandée/attribuée par le Layout.

QSize borderLayout::calculateSize(SizeType sizeType) const
{

    //totalSize est initialisée avec une valeur invalide (-1,-1):
    //totalSize.isvalid() renvoie faux
    //peut permetre de savoir si une QSize est encore initialisée ou pas manipulée...

    //QSize totalSize;
    //Ca me semble plus sain...
    QSize totalSize(0,0);


    for(int i = 0 ; i < list.size(); i++){
        //Difference entre list.value(i) et list.at(i) ?
        // si on est sur que i est dans les limites de la taille de la liste
        //il vaut mieux utiliser list.at(i) c'est plus rapide. list.value(i).
        //Si i est en dehors des bounds, il a un comportement plus correct que at.

        ItemWrapper * wrapper = list.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if(sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else
            itemSize = wrapper->item->sizeHint();

        //Calcule la taille en fonction de sa position sur le layout:

        //Height:
        if(position == North || position == South || position == Center){
            //rheight: returns a reference to the height.
            totalSize.rheight() += itemSize.height();
        }
        //Width:
        if(position == East || position == West || position == Center){
            totalSize.rwidth() += itemSize.width();
        }

    }

    qDebug()<<"totalSize = "<<totalSize;
    return totalSize;

}

//Construit la geometrie et le placement de chaque widget:
//Pour aller plus loin on pourra jouer sur les hauteurs, les frames de chaque widget
//(style bordure, epaisseur, couleur etc...)
void borderLayout::setGeometry(const QRect& Rect){

    qDebug()<<"call setGeometry inside, list size = "<<list.size();

    ItemWrapper *center = 0;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;

    //Voire notes cahier. Pour l'instant c'est comme ça. Un Rect recouvre le layout (sauf les marges)
    QLayout::setGeometry(Rect);

    for(int i = 0; i < list.size(); i++){

        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        //QRect::QRect(int x, int y, int width, int height) : construit un rectangle avec son coin haut/gauche (top left corner) a la coordonnée (x,y) et de largeur width et hauteur height

        //Geometrie et position des items nord et sud
        if(position == North){
            qDebug()<<"North";
            item->setGeometry( QRect(Rect.x(),northHeight, Rect.width(), item->sizeHint().height()) );

            northHeight += item->geometry().height() + spacing();
            //spacing() = -1 by default
        }
        else if (position == South){
            qDebug()<<"South";
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(),
                                    Rect.width(),
                                    item->sizeHint().height()));
            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(Rect.x(),
                                    Rect.y()+ Rect.height() - southHeight,
                                    item->geometry().width(),
                                    item->geometry().height()));
        }
        else if (position == Center){
            center = wrapper ;
        }
    }

    centerHeight = Rect.height() - northHeight - southHeight ;

    //Geometrie et position des widgets est et ouest:
    for(int i = 0; i < list.size(); i++){

        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if(position == West) {
            qDebug()<<"West";
            item->setGeometry(QRect(Rect.x() + westWidth + spacing(), northHeight,
                              item->sizeHint().width(), centerHeight));

            westWidth += item->geometry().width() + spacing();
        }
        else if (position == East) {

            //par defaut item->geometry.x() et y() sont égaux a 0.
            //Cales a l'origine en haut a gauche

            item->setGeometry(QRect(item->geometry().x(),northHeight,
                                    item->sizeHint().width(), centerHeight));

            qDebug()<<item->geometry().x()<<" "<<item->geometry().y();

            eastWidth += item->geometry().width() + spacing();

            //Shift du coté gauche
            item->setGeometry(QRect(
                                   Rect.x() + Rect.width() - eastWidth + spacing(),
                                   northHeight,
                                   item->geometry().width(),
                                   centerHeight));
        }
        if(center)
            center->item->setGeometry(QRect(
                                          westWidth,northHeight,
                                          Rect.width() - eastWidth - westWidth,
                                          centerHeight));

    }

    return;
}

