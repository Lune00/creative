#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

private:
    QPushButton * buttonA;
    QPushButton * buttonB;
};

#endif // WINDOW_H
