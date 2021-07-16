#include "widgetnewvocab.h"
#include "ui_widgetnewvocab.h"

// TODO verify if the vocab doesn't actually exist.

WidgetNewVocab::WidgetNewVocab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewVocab)
{
    ui->setupUi(this);
    enableEventForFirstStep();
}

void WidgetNewVocab::enableEventForFirstStep(){
    connect(ui->widget_2->getButton(), SIGNAL(clicked()), this, SLOT(runFirstButton()));
}

void WidgetNewVocab::runFirstButton(){
    ui->widget_2->getLabelError()->setText("");
    if(ui->widget_2->getLineEditForName()->text() == ""){
        ui->widget_2->getLabelError()->setText(tr("Vous n'avez pas rentrée de nom\n pour le nouveau vocabulaire."));
    }else if(ui->widget_2->getLineEditNumberOfColumn()->text() == ""){
        ui->widget_2->getLabelError()->setText(tr("Vous n'avez pas indiquée combien de colonne\n vous voulez avoir."));
    }else{
        if(!regex_match(ui->widget_2->getLineEditNumberOfColumn()->text().toStdString(), regex{"[+-]?[0-9]+"})){
            ui->widget_2->getLabelError()->setText(tr("La valeur entrée pour le nombre\n de colonne n'est pas un entier !"));
        }else{
            if(ui->widget_2->getLineEditNumberOfColumn()->text().toInt()<=1){
                ui->widget_2->getLabelError()->setText(tr("La valeur minimum requise est de 2."));
            }else if(ui->widget_2->getLineEditNumberOfColumn()->text().toInt()>4){
                ui->widget_2->getLabelError()->setText(tr("La valeur maximum requise est de 4."));
            }
            else{
                nameVocab = ui->widget_2->getNameLabel()->text().toStdString();
                numberOfColumn = ui->widget_2->getLineEditNumberOfColumn()->text().toInt();
                clearLayout(ui->widget_2->layout());
                WidgetNewVocabSecondStep *widgetSecondStep = new WidgetNewVocabSecondStep;
                listLineEdit.push_back(widgetSecondStep->getFirstLineEdit());
                listLineEdit.push_back(widgetSecondStep->getSecondLineEdit());


                for(int i=0; i<numberOfColumn-2;i++){
                    QLineEdit *qlineEdit = new QLineEdit;
                    listLineEdit.push_back(qlineEdit);
                    widgetSecondStep->addWidgetToLayout(qlineEdit);
                }
                errorLabelForNameColumn = widgetSecondStep->getErrorLabel();
                connect(widgetSecondStep->getValidButton(), SIGNAL(clicked()), this, SLOT(valideNameColumn()));

                ui->widget_2->layout()->addWidget(widgetSecondStep);
            }
        }
    }
}

void WidgetNewVocab::valideNameColumn(){

    if(verifLineEdit()){
        fileToSaveVocab.open(nameVocab+".vocab", ios::out);
        saveColumnName();
        fileToSaveVocab << numberOfColumn << endl;
        for(unsigned int i = 0; i<listNameColumn.size(); i++){
            fileToSaveVocab << listNameColumn.at(i);
            if(i<listNameColumn.size()-1){
                fileToSaveVocab <<";";
            }
        }
        fileToSaveVocab << endl;

        startLastStep();

    }

}

void WidgetNewVocab::startLastStep(){
    clearLayout(ui->widget_2->layout());

    WidgetNewVocabLastStep *widgetLastStep = new WidgetNewVocabLastStep;

    for(unsigned int i=0; i<listNameColumn.size(); i++){

        QPushButton *buttonAddWord = new QPushButton;
        buttonAddWord->setText("+");
        widgetLastStep->getLayoutForAddingBtn()->addWidget(buttonAddWord);
        listQPushButtonAdd.push_back(buttonAddWord);

        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(listNameColumn.at(i)));
        widgetLastStep->getLayoutForNameColumn()->addWidget(lblNameColumn);

        QVBoxLayout *hboxLayoutForListWord = new QVBoxLayout;
        listVBoxLayoutForListWord.push_back(hboxLayoutForListWord);
        QLineEdit *newLineEdit = new QLineEdit;
        hboxLayoutForListWord->addWidget(newLineEdit);
        listLineEditForWord.push_back(new vector<QLineEdit*>());
        listLineEditForWord.at(i)->push_back(newLineEdit);

        widgetLastStep->getLayoutForQLineEdit()->addLayout(hboxLayoutForListWord);

        QPushButton *buttonRemoveWord = new QPushButton;
        buttonRemoveWord->setEnabled(false);
        buttonRemoveWord->setText("-");
        widgetLastStep->getLayoutForRemovingBtn()->addWidget(buttonRemoveWord);
        listQPushButtonRemove.push_back(buttonRemoveWord);
    }

    ui->widget_2->layout()->addWidget(widgetLastStep);
}

void WidgetNewVocab::saveColumnName(){
    for(QLineEdit* lineEdit:listLineEdit){
        listNameColumn.push_back(lineEdit->text().toStdString());
    }
}

bool WidgetNewVocab::verifLineEdit(){
    errorLabelForNameColumn->setText("");
    for(QLineEdit* lineEdit:listLineEdit){
        if(lineEdit->text() == ""){
            errorLabelForNameColumn->setText(tr("Un des champs n'est pas rempli."));
            return false;
        }
    }
    return true;
}


void WidgetNewVocab::clearLayout(QLayout *layout, bool deleteWidgets){

    while(QLayoutItem* item = layout->takeAt(0))
    {
        if(deleteWidgets){
            if(QWidget* widget = item->widget()){
                widget->deleteLater();
            }
        }
        if(QLayout* childLayout = item->layout()){
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }

}

WidgetNewVocab::~WidgetNewVocab()
{
    delete ui;
}


















