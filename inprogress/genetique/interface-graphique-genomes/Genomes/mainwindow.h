#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createToolbar();
    void createMenu();

private:

    QAction* create_genome_;
    QAction* remove_genome_;
    QAction* options_;

    QAction* new_file_;
    QAction* load_file_;
    QAction* save_file_;

};

#endif // MAINWINDOW_H
