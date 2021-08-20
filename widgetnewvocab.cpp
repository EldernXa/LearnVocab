#include "widgetnewvocab.h"
#include "ui_widgetnewvocab.h"

// TODO verify if the vocab doesn't actually exist.
// TODO add qlineedit in the start and set their visible attribute to false.

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
                nameVocab = ui->widget_2->getLineEditForName()->text().toStdString();
                numberOfColumn = ui->widget_2->getLineEditNumberOfColumn()->text().toInt();
                clearLayout(ui->widget_2->layout());
                WidgetNewVocabSecondStep *widgetSecondStep = new WidgetNewVocabSecondStep;
                step = secondStep;
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
        for(QLineEdit* lineEdit : listLineEdit){
            listNameColumn.push_back(lineEdit->text().toStdString());
        }
        writerVocab = new WriterVocab(nameVocab, numberOfColumn, listNameColumn);

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

        connect(buttonAddWord, &QPushButton::clicked, this, [this, i]{addingWord(i);});
        connect(buttonRemoveWord, &QPushButton::clicked, this, [this, i]{removeWord(i);});
    }
    connect(widgetLastStep->getBtnAddWord(), SIGNAL(clicked()), this, SLOT(saveWord()));

    finishButton = widgetLastStep->getConfirmBtn();
    finishButton->setText(tr("Terminer le vocabulaire '%1'").arg(QString::fromStdString(nameVocab)));
    finishButton->setVisible(false);
    connect(finishButton, SIGNAL(clicked()), this, SLOT(finishVocab()));

    lblLastWord = widgetLastStep->getLblLastWord();
    errorInsertingWord = widgetLastStep->getLblError();


    ui->widget_2->layout()->addWidget(widgetLastStep);
}

void WidgetNewVocab::finishVocab(){
    for(unsigned int indexForVect=0; indexForVect<listLineEditForWord.size();indexForVect++){
        vector<QLineEdit *>::iterator it;
        unsigned int indexForLineEdit = listLineEditForWord.at(indexForVect)->size()-1;
        for(it = listLineEditForWord.at(indexForVect)->end()-1;
            it>=listLineEditForWord.at(indexForVect)->begin();it--){
            delete listLineEditForWord.at(indexForVect)->at(indexForLineEdit);
            listLineEditForWord.at(indexForVect)->erase(it);
            indexForLineEdit--;
        }
    }
    if(writerVocab != nullptr)
        writerVocab->close();
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void WidgetNewVocab::saveWord(){
    if(verifyInputWord()){
        lblLastWord->setText(tr("Le dernier mot sauvegardée contenait le mot : %1.").arg(listLineEditForWord.at(0)->at(0)->text()));
        writerVocab->addLine(listLineEditForWord);

        for(unsigned int indexForVect=0; indexForVect<listLineEditForWord.size(); indexForVect++){
            vector<QLineEdit*>::iterator it;
            unsigned int indexForLineEdit = listLineEditForWord.at(indexForVect)->size()-1;
            for(it = listLineEditForWord.at(indexForVect)->end()-1;
                it>= listLineEditForWord.at(indexForVect)->begin()+1; it--){
                delete listLineEditForWord.at(indexForVect)->at(indexForLineEdit);
                listLineEditForWord.at(indexForVect)->erase(it);
                indexForLineEdit--;
            }
            listLineEditForWord.at(indexForVect)->at(0)->clear();
        }

        finishButton->setVisible(true);
        errorInsertingWord->setText("");
    }else{
        errorInsertingWord->setText(tr("Vous n'avez pas remplis tous les champs de texte."));
    }
}

bool WidgetNewVocab::verifyInputWord(){
    for(auto *var : listLineEditForWord){
        for(auto *lineEdit: *var){
            if(lineEdit->text() ==""){
                return false;
            }
        }
    }
    return true;
}

void WidgetNewVocab::addingWord(int num){
    QLineEdit *newLineEdit = new QLineEdit;
    listVBoxLayoutForListWord.at(num)->addWidget(newLineEdit);
    listLineEditForWord.at(num)->push_back(newLineEdit);

    listQPushButtonRemove.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==LIMIT_NUMBER_WORD){
        listQPushButtonAdd.at(num)->setEnabled(false);
    }
}

void WidgetNewVocab::removeWord(int num){
    delete listLineEditForWord.at(num)->at(listLineEditForWord.at(num)->size()-1);
    listLineEditForWord.at(num)->erase(listLineEditForWord.at(num)->end()-1);

    listQPushButtonAdd.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==1){
        listQPushButtonRemove.at(num)->setEnabled(false);
    }
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

void WidgetNewVocab::resizeEvent(QResizeEvent* event){
    if(step == initStep){
        GlobalFct::changeSizeFontOfLbl(ui->widget_2->getLabelError(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLineEdit(ui->widget_2->getLineEditForName(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLineEdit(ui->widget_2->getLineEditNumberOfColumn(), this->width(), this->height());
        GlobalFct::changeSizeFontOfPushButton(ui->widget_2->getButton(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLbl(ui->widget_2->getNameLabel(), this->width(), this->height());
        GlobalFct::changeSizeFontOfLbl(ui->widget_2->getNumberColumnLabel(), this->width(), this->height());
    }
    QWidget::resizeEvent(event);
}

WidgetNewVocab::~WidgetNewVocab()
{
    finishVocab();
    delete ui;
}


















