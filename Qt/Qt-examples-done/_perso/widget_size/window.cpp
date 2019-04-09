#include "window.h"
#include <QHBoxLayout>

//La notion de size min et max n'a de sens que dans un Layout
Window::Window()
{

    QLayout * layout = new QHBoxLayout ;


    buttonA = new QPushButton("BlablaBla");
    buttonB = new QPushButton("B");

    QSize minSizeA = QSize(200,20);
    QSize maxSizeA = QSize(400,50);
    QSize minSizeB = QSize(200,10);
    QSize maxSizeB = QSize(400,50);

    buttonA->setMinimumSize(minSizeA);
    buttonA->setMaximumSize(maxSizeA);

    buttonB->setMinimumSize(minSizeB);
    buttonB->setMaximumSize(maxSizeB);

    layout->addWidget(buttonA);
    layout->addWidget(buttonB);
    setLayout(layout);

    qDebug()<<"button A minimumSize ="<<buttonA->minimumSize();
    qDebug()<<"button A minimumSizeHint ="<<buttonA->minimumSizeHint();
    qDebug()<<"button A HintSize ="<<buttonA->sizeHint();
    qDebug()<<"button A actual size ="<<buttonA->size();
}

Window::~Window()
{
}
