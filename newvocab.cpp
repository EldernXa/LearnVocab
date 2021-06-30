#include "newvocab.h"
#include "ui_newvocab.h"

using namespace std;

// TODO verify if the vocab doesn't actually exist.

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
        ui->labelError->setText(tr("Vous n'avez pas rentrée de nom\n pour le nouveau vocabulaire."));
    }
    else if(ui->lineEditNumberOfColumn->text() == ""){
        ui->labelError->setText(tr("Vous n'avez pas indiquée combien de colonne\n vous voulez avoir."));
    }else{
        if(!regex_match(ui->lineEditNumberOfColumn->text().toStdString(), std::regex{"[+-]?[0-9]+"})){
            ui->labelError->setText(tr("La valeur entrée pour le nombre\n de colonne n'est pas un entier !"));
        }else{
            if(ui->lineEditNumberOfColumn->text().toInt()<=1){
                ui->labelError->setText(tr("Valeur minimum requise est de 2."));
            }else if(ui->lineEditNumberOfColumn->text().toInt()>4){
                ui->labelError->setText(tr("Valeur maximum permise est de 4."));
            }
            else{
                nameVocab = ui->lineEditForName->text().toStdString();
                clearLayout(ui->layoutForCreateNewVocab);
                QVBoxLayout *newQVBoxLayout = new QVBoxLayout;
                ui->centralwidget->setLayout(newQVBoxLayout);
                QLabel *newlbl = new QLabel;
                newlbl->setText(tr("Nom des colonnes :"));
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
                termineAddingNameForColumn->setText(tr("Valider"));
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
        QWidget *mainWidget = new QWidget;
        QWidget *otherWidget = new QWidget(mainWidget);
        setCentralWidget(mainWidget);

        // Layout for adding new word in vocab.
        QWidget *widgetForAddingWord = new QWidget(mainWidget);
        otherWidget->move(0, HEIGHT_WIDGET);
        QHBoxLayout *layoutForButtonAddWord = new QHBoxLayout(widgetForAddingWord);
        layoutForButtonAddWord->sizeConstraint();

        QWidget *widgetForDisplayColumn = new QWidget(mainWidget);
        QHBoxLayout *displayColumn = new QHBoxLayout(widgetForDisplayColumn);
        displayColumn->sizeConstraint();
        widgetForDisplayColumn->move(0, HEIGHT_WIDGET+10);

        QWidget *widgetForBoxAllWord = new QWidget(mainWidget);
        QHBoxLayout *boxAllWord = new QHBoxLayout(widgetForBoxAllWord);
        widgetForBoxAllWord->move(0, HEIGHT_WIDGET*2+10);
        widgetForBoxAllWord->setFixedHeight((LIMIT_NUMBER_WORD)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD));

        // Layout for remove word in vocab.
        QWidget *widgetForRemovingWord = new QWidget(mainWidget);
        QHBoxLayout *layoutForButtonRemoveWord = new QHBoxLayout(widgetForRemovingWord);
        layoutForButtonRemoveWord->sizeConstraint();
        widgetForRemovingWord->move(0, (LIMIT_NUMBER_WORD+4)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD+4) - HEIGHT_WIDGET);


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

        QPushButton *validButton = new QPushButton(mainWidget);
        validButton->setText(tr("Ajouter le mot"));
        validButton->setFixedWidth(WIDTH_WIDGET);
        connect(validButton, SIGNAL(clicked()), this, SLOT(saveWord()));
        validButton->move(0, (LIMIT_NUMBER_WORD+6)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD+6) - validButton->height());

        finishButton = new QPushButton(mainWidget);
        finishButton->setText(tr("Terminer le vocabulaire") + QString::fromStdString(" '" +nameVocab + "'"));
        finishButton->setFixedWidth(WIDTH_WIDGET);
        finishButton->setVisible(false);
        connect(finishButton, SIGNAL(clicked()), this, SLOT(finishVocab()));
        finishButton->move(WIDTH_WIDGET+50,
                           (LIMIT_NUMBER_WORD+6)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD+6) - finishButton->height());

        lblLastWord = new QLabel(mainWidget);
        lblLastWord->setText("");
        lblLastWord->setFixedWidth(1000);
        lblLastWord->move(0,(LIMIT_NUMBER_WORD+6)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD+6));

        errorInsertingWord = new QLabel(mainWidget);
        errorInsertingWord->setText("");
        errorInsertingWord->setStyleSheet("QLabel {color:red;}");
        errorInsertingWord->setFixedWidth(1000);
        errorInsertingWord->move(0, (LIMIT_NUMBER_WORD+7)*HEIGHT_WIDGET + boxAllWord->spacing()*(LIMIT_NUMBER_WORD+7));

        addWord = true;
        this->setFixedHeight((LIMIT_NUMBER_WORD+mainWidget->children().size())*HEIGHT_WIDGET + boxAllWord->spacing()
                             * (LIMIT_NUMBER_WORD+mainWidget->children().size()));
        addWord = false;

        mainWidget->setFixedHeight((LIMIT_NUMBER_WORD+mainWidget->children().size())*HEIGHT_WIDGET +
                                   boxAllWord->spacing()*(LIMIT_NUMBER_WORD+mainWidget->children().size()));
        otherWidget->setFixedHeight((LIMIT_NUMBER_WORD+mainWidget->children().size()-1)*HEIGHT_WIDGET +
                                    boxAllWord->spacing()*(LIMIT_NUMBER_WORD+mainWidget->children().size()-1));
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
    if(verifyInputWord()){
        lblLastWord->setText(tr("Le dernier mot sauvegardée contenait le mot : ") + listLineEditForWord.at(0)->at(0)->text()+".");
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
        errorInsertingWord->setText("");
    }else
    {
        errorInsertingWord->setText(tr("Vous avez pas remplis tous les champs de texte."));
    }
}

bool NewVocab::verifyInputWord(){
    for(auto *var : listLineEditForWord){
        for(auto *lineEdit : *var){
            if(lineEdit->text() == ""){
                return false;
            }
        }
    }
    return true;
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
}

void NewVocab::removeWord(int num){
    delete listLineEditForWord.at(num)->at(listLineEditForWord.at(num)->size()-1);
    listLineEditForWord.at(num)->erase(listLineEditForWord.at(num)->end()-1);

    listQPushButtonAdd.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==1){
        listQPushButtonRemove.at(num)->setEnabled(false);
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
            errorLabelForNameColumn->setText(tr("Un des champs n'est pas rempli."));
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
