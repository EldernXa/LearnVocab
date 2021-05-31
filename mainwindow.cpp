#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enableEvent();
}

void MainWindow::enableEvent(){
    connect(ui->saveNewVocab, SIGNAL(clicked()), this, SLOT(newfunction()));
}

void MainWindow::newfunction(){
    NewVocab *newVocab = new NewVocab(this);
    newVocab->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

