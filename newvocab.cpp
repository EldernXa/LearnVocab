#include "newvocab.h"
#include "ui_newvocab.h"

using namespace std;

// TODO change string for future translation.
// TODO Put number into variable cst.
// TODO remove the resize to set the size initially.

NewVocab::NewVocab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewVocab)
{
    ui->setupUi(this);
    ui->widgetForCreateNewVocab->adjustSize();
    this->resize(ui->widgetForCreateNewVocab->width()+40, ui->widgetForCreateNewVocab->height()+40);
    enableEvent();
    ui->labelError->setStyleSheet("QLabel {color:red;}");
    errorLabelForNameColumn->setStyleSheet("QLabel {color:red;}");
}

void NewVocab::resizeEvent(QResizeEvent *qresizeEvent){
    if(!addWord){
        this->setFixedWidth(ui->widgetForCreateNewVocab->width()+40);
        this->setFixedHeight(ui->widgetForCreateNewVocab->height()+40);
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
                newQVBoxLayout->addWidget(errorLabelForNameColumn);
                connect(termineAddingNameForColumn, SIGNAL(clicked()), this, SLOT(valideNameColumn()));
            }
        }
    }
}

void NewVocab::valideNameColumn(){
    fstream file;

    file.open(nameVocab+".vocab", ios::out);
    if(verifLineEdit()){
        saveColumnName();
        file << numberOfColumn << endl;
        for(unsigned int i=0; i<listNameColumn.size();i++){
            file << listNameColumn.at(i);
            if(i<listNameColumn.size()-1){
                file<<";";
            }
        }
        file << endl;
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
            lblNameColumn->setFixedWidth(250);
            lblNameColumn->setFixedHeight(20);
            lblNameColumn->setText(QString::fromStdString(listNameColumn.at(i)));
            displayColumn->addWidget(lblNameColumn);

            QVBoxLayout *hboxLayoutForListWord = new QVBoxLayout;
            listVBoxLayoutForListWord.push_back(hboxLayoutForListWord);
            QLineEdit *newLineEdit = new QLineEdit;
            newLineEdit->setFixedWidth(250);
            newLineEdit->setFixedHeight(20);
            hboxLayoutForListWord->addWidget(newLineEdit);
            listLineEditForWord.push_back(new std::vector<QLineEdit*>());
            listLineEditForWord.at(i)->push_back(newLineEdit);

            boxAllWord->addLayout(hboxLayoutForListWord);

            QPushButton *buttonAddWord = new QPushButton;
            buttonAddWord->setText("+");
            buttonAddWord->setFixedWidth(250);
            layoutForButtonAddWord->addWidget(buttonAddWord);
            listQPushButtonAdd.push_back(buttonAddWord);

            QPushButton *buttonRemoveWord = new QPushButton;
            buttonRemoveWord->setEnabled(false);
            buttonRemoveWord->setText("-");
            buttonRemoveWord->setFixedWidth(250);
            layoutForButtonRemoveWord->addWidget(buttonRemoveWord);
            listQPushButtonRemove.push_back(buttonRemoveWord);


            connect(buttonAddWord, &QPushButton::clicked, this, [this, i]{addingWord(i);});
            connect(buttonRemoveWord, &QPushButton::clicked, this, [this, i]{removeWord(i);});
        }

        QPushButton *validButton = new QPushButton;
        validButton->setText("Ajouter le mot");
        validButton->setFixedWidth(250);
        newQVBoxLayout->addWidget(validButton);
        connect(validButton, SIGNAL(clicked()), this, SLOT(saveWord()));
    }
    file.close();
}

void NewVocab::saveWord(){
    // FIXME mustn't recreate the file.
    fstream file;
    file.open(nameVocab+".vocab", ios::out);
    for(unsigned int indexForVect=0 ; indexForVect<listLineEditForWord.size();indexForVect++){
        for(unsigned int indexForLineEdit = 0; indexForLineEdit<listLineEditForWord.at(indexForVect)->size(); indexForLineEdit++){
            file << listLineEditForWord.at(indexForVect)->at(indexForLineEdit)->text().toStdString();
            if(indexForLineEdit<listLineEditForWord.at(indexForVect)->size()-1){
                file<<",";
            }
        }
        if(indexForVect < listLineEditForWord.size()-1){
            file<<";";
        }else{
            file<<endl;
        }
    }
    file.close();
}

void NewVocab::addingWord(int num){
    QLineEdit *newLineEdit = new QLineEdit;
    newLineEdit->setFixedWidth(250);
    newLineEdit->setFixedHeight(20);
    listVBoxLayoutForListWord.at(num)->addWidget(newLineEdit);
    listLineEditForWord.at(num)->push_back(newLineEdit);

    listQPushButtonRemove.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==5){
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
        this->setFixedHeight(this->height()+20);

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
        this->setFixedHeight(this->height()-20);
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

NewVocab::~NewVocab()
{
    delete ui;
}
