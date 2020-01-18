#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

class GenomeWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createToolbar();
    void createMenu();
    void connectActions();

private slots:
    void updateActions(const QItemSelection& selection);
    void openFile();
    void saveFile();

private:
    QAction* create_genome_;
    QAction* remove_genome_;
    QAction* options_;

    QAction* new_file_;
    QAction* load_file_;
    QAction* save_file_;

    GenomeWidget* genomeWidget_;

};

#endif // MAINWINDOW_H
