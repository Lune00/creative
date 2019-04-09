#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

private:
    QLabel * createLabel(const QString& text );
};

#endif // WINDOW_H
