#include "newvocab.h"
#include "ui_newvocab.h"

NewVocab::NewVocab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewVocab)
{
    ui->setupUi(this);
    ui->widgetForCreateNewVocab->adjustSize();
    this->resize(ui->widgetForCreateNewVocab->width()+40, ui->widgetForCreateNewVocab->height()+40);
    enableEvent();
}

void NewVocab::resizeEvent(QResizeEvent *qresizeEvent){
    this->setFixedWidth(ui->widgetForCreateNewVocab->width()+40);
    this->setFixedHeight(ui->widgetForCreateNewVocab->height()+40);
    QWidget::resizeEvent(qresizeEvent);
}

void NewVocab::enableEvent(){
    connect(ui->firstButtonForCreateVocab, SIGNAL(clicked()), this, SLOT(runFirstButton()));
}

void NewVocab::runFirstButton(){
    if(ui->lineEditForName->text()!=""){
        while ( QWidget* w = findChild<QWidget*>() )
            delete w;
    }
}

NewVocab::~NewVocab()
{
    delete ui;
}
