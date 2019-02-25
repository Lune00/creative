#include "mainwindow.h"
#include "options.h"

#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>

#include"genomewidget.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
    genomeWidget_ = new GenomeWidget(parent);

    createActions();
    connectActions();
    createToolbar();
    createMenu();

    setCentralWidget(genomeWidget_);

    //Solution pour ne pas pouvoir masquer la toolbar (solution tmp)
    //setContextMenuPolicy(Qt::PreventContextMenu);
    setWindowTitle("Bibliothèque de Génomes");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    create_genome_ = new QAction( QIcon(":/icons/Add.png"),"&Ajouter un génome",this);
    //Ajoute un Genome vide juste avec un nom (verifie qu'il existe pas deja)
    remove_genome_ = new QAction(QIcon(":/icons/Remove.png"),"&Supprimer le ou les génomes sélectionés",this);
    options_ = new QAction(QIcon(":/icons/ADN.png"),"&Paramètres génétiques",this);

    //Ajouter un bouton "Editer genome selectioné" (un seul à la fois) (equivalant a double clicker dessus)

    new_file_ = new QAction("Nouveau fichier",this);
    load_file_ = new QAction("Ouvrir un fichier",this);
    save_file_ = new QAction("Sauvegarder [nom fichier en cours]",this);

}

void MainWindow::connectActions(){

    connect(create_genome_,&QAction::triggered,genomeWidget_,&GenomeWidget::showAddEntryDialog);

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

void MainWindow::updateActions(const QItemSelection& selection){


}

void MainWindow::openFile(){

}

void MainWindow::saveFile(){

}
