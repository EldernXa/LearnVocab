#include "newvocab.h"
#include "ui_newvocab.h"

using namespace std;

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
    if(ui->lineEditForName->text()!="" && ui->lineEditNumberOfColumn->text()!=""){
        nameVocab = ui->lineEditForName->text().toStdString();
        clearLayout(ui->layoutForCreateNewVocab);
        QVBoxLayout *newQVBoxLayout = new QVBoxLayout;
        ui->centralwidget->setLayout(newQVBoxLayout);
        QLabel *newlbl = new QLabel;
        newlbl->setText("Nom des colonnes :");
        newQVBoxLayout->addWidget(newlbl);
        QHBoxLayout *hboxLayout = new QHBoxLayout;
        hboxLayout->setSpacing(2);
        newQVBoxLayout->addLayout(hboxLayout);
        numberOfColumn = ui->lineEditNumberOfColumn->text().toInt();
        this->setFixedWidth(250*numberOfColumn+40);
        ui->centralwidget->setFixedWidth(250*numberOfColumn+40+5*numberOfColumn);
        for(int i=0; i<numberOfColumn; i++){
            QLineEdit *qlineEdit = new QLineEdit;
            qlineEdit->setFixedWidth(250);
            listLineEdit.push_back(qlineEdit);
            hboxLayout->addWidget(qlineEdit);
        }
        QPushButton *termineAddingNameForColumn = new QPushButton;
        termineAddingNameForColumn->setText("Valider");
        termineAddingNameForColumn->setFixedWidth(250);
        newQVBoxLayout->addWidget(termineAddingNameForColumn);
        connect(termineAddingNameForColumn, SIGNAL(clicked()), this, SLOT(valideNameColumn()));
    }
}

void NewVocab::valideNameColumn(){
    cout << "ok ok" << endl;
}

void NewVocab::clearLayout(QLayout *layout){
    QLayoutItem *item;
     while ((item = layout->takeAt(0))){
         item->widget()->deleteLater();
     }
}

NewVocab::~NewVocab()
{
    delete ui;
}
