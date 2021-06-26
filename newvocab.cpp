#include "newvocab.h"
#include "ui_newvocab.h"

using namespace std;

// verify if the vocab doesn't actually exist.
// TODO change string for future translation.
// TODO remove the resize to set the size initially.
// display the last word saved

NewVocab::NewVocab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewVocab)
{
    ui->setupUi(this);
    ui->widgetForCreateNewVocab->adjustSize();
    this->resize(ui->widgetForCreateNewVocab->width()+WIDTH_LINE_EDIT_WORD, ui->widgetForCreateNewVocab->height()+HEIGHT_LINE_EDIT_WORD);
    enableEvent();
    ui->labelError->setStyleSheet("QLabel {color:red;}");
    errorLabelForNameColumn->setStyleSheet("QLabel {color:red;}");
}

NewVocab::~NewVocab(){
    fileToSaveVocab.close();
}

void NewVocab::closeEvent(QCloseEvent *event){
    fileToSaveVocab.close();
    QWidget::closeEvent(event);
}

void NewVocab::resizeEvent(QResizeEvent *qresizeEvent){
    if(!addWord){
        this->setFixedWidth(ui->widgetForCreateNewVocab->width()+WIDTH_LINE_EDIT_WORD);
        this->setFixedHeight(ui->widgetForCreateNewVocab->height()+HEIGHT_LINE_EDIT_WORD);
        QWidget::resizeEvent(qresizeEvent);
    }
}

void NewVocab::enableEvent(){
    connect(ui->firstButtonForCreateVocab, SIGNAL(clicked()), this, SLOT(runFirstButton()));
}

void NewVocab::runFirstButton(){
    ui->labelError->setText("");
    if(ui->lineEditForName->text() == ""){
        ui->labelError->setText("Vous n'avez pas rentrée de nom\n pour le nouveau vocabulaire.");
    }
    else if(ui->lineEditNumberOfColumn->text() == ""){
        ui->labelError->setText("Vous n'avez pas indiquée combien de colonne\n vous voulez avoir.");
    }else{
        if(!regex_match(ui->lineEditNumberOfColumn->text().toStdString(), std::regex{"[+-]?[0-9]+"})){
            ui->labelError->setText("La valeur entrée pour le nombre\n de colonne n'est pas un entier !");
        }else{
            if(ui->lineEditNumberOfColumn->text().toInt()<=1){
                ui->labelError->setText("Valeur minimum requise est de 2.");
            }else if(ui->lineEditNumberOfColumn->text().toInt()>4){
                ui->labelError->setText("Valeur maximum permise est de 4.");
            }
            else{
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
                this->setFixedWidth(WIDTH_WIDGET*numberOfColumn+WIDTH_LINE_EDIT_WORD);
                ui->centralwidget->setFixedWidth(WIDTH_WIDGET*numberOfColumn+WIDTH_LINE_EDIT_WORD+LIMIT_NUMBER_WORD*numberOfColumn);
                for(int i=0; i<numberOfColumn; i++){
                    QLineEdit *qlineEdit = new QLineEdit;
                    qlineEdit->setFixedWidth(WIDTH_WIDGET);
                    listLineEdit.push_back(qlineEdit);
                    hboxLayout->addWidget(qlineEdit);
                }
                QPushButton *termineAddingNameForColumn = new QPushButton;
                termineAddingNameForColumn->setText("Valider");
                termineAddingNameForColumn->setFixedWidth(WIDTH_WIDGET);
                newQVBoxLayout->addWidget(termineAddingNameForColumn);
                newQVBoxLayout->addWidget(errorLabelForNameColumn);
                connect(termineAddingNameForColumn, SIGNAL(clicked()), this, SLOT(valideNameColumn()));
            }
        }
    }
}

void NewVocab::valideNameColumn(){

    fileToSaveVocab.open(nameVocab+".vocab", ios::out);
    if(verifLineEdit()){
        saveColumnName();
        fileToSaveVocab << numberOfColumn << endl;
        for(unsigned int i=0; i<listNameColumn.size();i++){
            fileToSaveVocab << listNameColumn.at(i);
            if(i<listNameColumn.size()-1){
                fileToSaveVocab<<";";
            }
        }
        fileToSaveVocab << endl;
        QWidget *newWidget = new QWidget;
        QVBoxLayout *newQVBoxLayout = new QVBoxLayout;
        newWidget->setLayout(newQVBoxLayout);
        setCentralWidget(newWidget);
        QHBoxLayout *layoutForButtonAddWord = new QHBoxLayout;
        newQVBoxLayout->addLayout(layoutForButtonAddWord);
        QHBoxLayout *displayColumn = new QHBoxLayout;
        newQVBoxLayout->addLayout(displayColumn);
        QHBoxLayout *boxAllWord = new QHBoxLayout;
        newQVBoxLayout->addLayout(boxAllWord);
        QHBoxLayout *layoutForButtonRemoveWord = new QHBoxLayout;
        newQVBoxLayout->addLayout(layoutForButtonRemoveWord);
        for(unsigned int i=0; i<listNameColumn.size(); i++){
            QLabel *lblNameColumn = new QLabel;
            lblNameColumn->setFixedWidth(WIDTH_WIDGET);
            lblNameColumn->setFixedHeight(HEIGHT_WIDGET);
            lblNameColumn->setText(QString::fromStdString(listNameColumn.at(i)));
            displayColumn->addWidget(lblNameColumn);

            QVBoxLayout *hboxLayoutForListWord = new QVBoxLayout;
            listVBoxLayoutForListWord.push_back(hboxLayoutForListWord);
            QLineEdit *newLineEdit = new QLineEdit;
            newLineEdit->setFixedWidth(WIDTH_WIDGET);
            newLineEdit->setFixedHeight(HEIGHT_WIDGET);
            hboxLayoutForListWord->addWidget(newLineEdit);
            listLineEditForWord.push_back(new std::vector<QLineEdit*>());
            listLineEditForWord.at(i)->push_back(newLineEdit);

            boxAllWord->addLayout(hboxLayoutForListWord);

            QPushButton *buttonAddWord = new QPushButton;
            buttonAddWord->setText("+");
            buttonAddWord->setFixedWidth(WIDTH_WIDGET);
            layoutForButtonAddWord->addWidget(buttonAddWord);
            listQPushButtonAdd.push_back(buttonAddWord);

            QPushButton *buttonRemoveWord = new QPushButton;
            buttonRemoveWord->setEnabled(false);
            buttonRemoveWord->setText("-");
            buttonRemoveWord->setFixedWidth(WIDTH_WIDGET);
            layoutForButtonRemoveWord->addWidget(buttonRemoveWord);
            listQPushButtonRemove.push_back(buttonRemoveWord);


            connect(buttonAddWord, &QPushButton::clicked, this, [this, i]{addingWord(i);});
            connect(buttonRemoveWord, &QPushButton::clicked, this, [this, i]{removeWord(i);});
        }

        QHBoxLayout *layoutForButton = new QHBoxLayout;

        QPushButton *validButton = new QPushButton;
        validButton->setText("Ajouter le mot");
        validButton->setFixedWidth(WIDTH_WIDGET);
        layoutForButton->addWidget(validButton);
        connect(validButton, SIGNAL(clicked()), this, SLOT(saveWord()));

        finishButton = new QPushButton;
        finishButton->setText(QString::fromStdString("Terminer le vocabulaire '" + nameVocab + "'"));
        finishButton->setFixedWidth(WIDTH_WIDGET);
        finishButton->setVisible(false);
        layoutForButton->addWidget(finishButton);
        connect(finishButton, SIGNAL(clicked()), this, SLOT(finishVocab()));

        newQVBoxLayout->addLayout(layoutForButton);
    }
}

void NewVocab::finishVocab(){
    for(unsigned int indexForVect=0; indexForVect<listLineEditForWord.size(); indexForVect++){
        vector<QLineEdit*>::iterator it;
        unsigned int indexForLineEdit = listLineEditForWord.at(indexForVect)->size()-1;
        for(it = listLineEditForWord.at(indexForVect)->end()-1 ;
            it>=listLineEditForWord.at(indexForVect)->begin(); it--){
            delete listLineEditForWord.at(indexForVect)->at(indexForLineEdit);
            listLineEditForWord.at(indexForVect)->erase(it);
            indexForLineEdit--;
        }
    }
    fileToSaveVocab.close();
    this->close();
}

void NewVocab::saveWord(){
    // TODO verify if all input aren't empty before saving.
    for(unsigned int indexForVect=0 ; indexForVect<listLineEditForWord.size();indexForVect++){
        for(unsigned int indexForLineEdit = 0; indexForLineEdit<listLineEditForWord.at(indexForVect)->size(); indexForLineEdit++){
            fileToSaveVocab << listLineEditForWord.at(indexForVect)->at(indexForLineEdit)->text().toStdString();
            if(indexForLineEdit<listLineEditForWord.at(indexForVect)->size()-1){
                fileToSaveVocab<<",";
            }
        }
        if(indexForVect < listLineEditForWord.size()-1){
            fileToSaveVocab<<";";
        }else{
            fileToSaveVocab<<endl;
        }
    }

    for(unsigned int indexForVect=0; indexForVect<listLineEditForWord.size(); indexForVect++){
        vector<QLineEdit*>::iterator it;
        unsigned int indexForLineEdit = listLineEditForWord.at(indexForVect)->size()-1;
        for(it = listLineEditForWord.at(indexForVect)->end()-1;
            it>=listLineEditForWord.at(indexForVect)->begin()+1; it--){
            delete listLineEditForWord.at(indexForVect)->at(indexForLineEdit);
            listLineEditForWord.at(indexForVect)->erase(it);
            indexForLineEdit--;
        }
        listLineEditForWord.at(indexForVect)->at(0)->clear();
    }

    finishButton->setVisible(true);

}

void NewVocab::addingWord(int num){
    QLineEdit *newLineEdit = new QLineEdit;
    newLineEdit->setFixedWidth(WIDTH_WIDGET);
    newLineEdit->setFixedHeight(HEIGHT_WIDGET);
    listVBoxLayoutForListWord.at(num)->addWidget(newLineEdit);
    listLineEditForWord.at(num)->push_back(newLineEdit);

    listQPushButtonRemove.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==LIMIT_NUMBER_WORD){
        listQPushButtonAdd.at(num)->setEnabled(false);
    }

    bool verif = true;
    unsigned int otherNum = num;
    for(unsigned int i = 0; i<listLineEditForWord.size(); i++){
        if(i!=otherNum){
            if(listLineEditForWord.at(i)->size()>=listLineEditForWord.at(otherNum)->size()){
                verif = false;
            }
        }
    }

    if(verif){
        addWord = true;
        this->setFixedHeight(this->height()+HEIGHT_WIDGET);

        addWord = false;
    }
}

void NewVocab::removeWord(int num){
    delete listLineEditForWord.at(num)->at(listLineEditForWord.at(num)->size()-1);
    listLineEditForWord.at(num)->erase(listLineEditForWord.at(num)->end()-1);

    listQPushButtonAdd.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==1){
        listQPushButtonRemove.at(num)->setEnabled(false);
    }

    bool verif = true;
    unsigned int unsignedNum = num;
    for(unsigned int i = 0; i<listLineEditForWord.size(); i++){
        if(i!=unsignedNum){
            if(listLineEditForWord.at(i)->size()>listLineEditForWord.at(unsignedNum)->size()){
                verif = false;
            }
        }
    }

    if(verif){
        addWord = true;
        this->setFixedHeight(this->height()-HEIGHT_WIDGET);
        addWord = false;
    }
}

void NewVocab::saveColumnName(){
    for(QLineEdit* lineEdit : listLineEdit){
        listNameColumn.push_back(lineEdit->text().toStdString());
    }
}

bool NewVocab::verifLineEdit(){
    errorLabelForNameColumn->setText("");
    for(QLineEdit* lineEdit:listLineEdit){
        if(lineEdit->text() == ""){
            errorLabelForNameColumn->setText("Un des champs n'est pas rempli.");
        }
    }

    return true;
}

void NewVocab::clearLayout(QLayout *layout){
    for(int i=0; i<layout->count();i++){
        delete layout->takeAt(i)->widget();
    }
    QLayoutItem *item;
     while ((item = layout->takeAt(0))){
        item->widget()->deleteLater();
     }
}
