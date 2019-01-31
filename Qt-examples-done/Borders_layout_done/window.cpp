#include "window.h"
#include "borderlayout.h"
#include <QTextBrowser>

Window::Window()
{
    //Central Widget:
    QTextBrowser * centralWidget = new QTextBrowser;
    centralWidget->setPlainText("Bienvenue!");

    //North Widget:
    QLabel * northWidget = createLabel("Nord");
    QLabel * southWidget = createLabel("Sud");
    QLabel * westWidget = createLabel("West");
    QLabel * east1Widget = createLabel("East1");
    QLabel * east2Widget = createLabel("East2");
    QLabel * east3Widget = createLabel("East3");

    //Defaut constructor:
    borderLayout * layout = new borderLayout;

    layout->addWidget(centralWidget,borderLayout::Center);
    layout->addWidget(northWidget,borderLayout::North);
    layout->addWidget(westWidget,borderLayout::West);
    layout->addWidget(east3Widget,borderLayout::East);
    layout->addWidget(east2Widget,borderLayout::East);
    layout->addWidget(east1Widget,borderLayout::East);
    layout->addWidget(southWidget,borderLayout::South);

    setLayout(layout);

    setWindowTitle("Borders Layout");
}

Window::~Window()
{

}

QLabel * Window::createLabel(const QString& text){
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}
