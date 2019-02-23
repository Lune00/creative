#include "mainwindow.h"
#include "options.h"
#include "genomebank.h"

#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
    createActions();
    createToolbar();
    createMenu();

    //Solution pour ne pas pouvoir masquer la toolbar (solution tmp)
    setContextMenuPolicy(Qt::PreventContextMenu);

    //setCentralWidget(new GenomeBank);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    create_genome_ = new QAction( QIcon(":/icons/Add.png"),"&Creer un genome",this);
    remove_genome_ = new QAction(QIcon(":/icons/Remove.png"),"&Supprimer un genome",this);
    options_ = new QAction(QIcon(":/icons/ADN.png"),"&Paramètres génétiques",this);

    new_file_ = new QAction("Nouveau fichier",this);
    load_file_ = new QAction("Ouvrir un fichier",this);
    save_file_ = new QAction("Sauvegarder [nom fichier en cours]",this);

}

void MainWindow::createToolbar()
{
    //Toolbar:
    QToolBar* toolbar = new QToolBar;
    addToolBar(Qt::TopToolBarArea,toolbar);

    toolbar->addAction(create_genome_);
    toolbar->addAction(remove_genome_);
    toolbar->addAction(options_);
    toolbar->setIconSize(QSize(22,22));
}

void MainWindow::createMenu()
{
    //Menu:
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(new_file_);
    fileMenu->addAction(load_file_);
    fileMenu->addAction(save_file_);
    QMenu *GenomeMenu = menuBar()->addMenu(tr("&Genome"));
    GenomeMenu->addAction(create_genome_);
    GenomeMenu->addAction(remove_genome_);
    GenomeMenu->addAction(options_);
    //QMenu *HelpMenu = menuBar()->addMenu(tr("&Aide"));
}
