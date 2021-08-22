#include "addword.h"
#include "ui_addword.h"

AddWord::AddWord(string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWord)
{
    ui->setupUi(this);
    this->nameVocab = nameVocab;
    ReaderVocab *readerVocab = new ReaderVocab(nameVocab);
    writerVocab = new WriterVocab(nameVocab);
    vector<string> listNameColumn = readerVocab->getColumnName();
    for(unsigned int i = 0; i<listNameColumn.size(); i++){
        QPushButton *buttonAddWord = new QPushButton;
        buttonAddWord->setText("+");
        ui->widget->getLayoutForAddingBtn()->addWidget(buttonAddWord);
        listQPushButtonAdd.push_back(buttonAddWord);
        GlobalFct::changeSizeFontOfPushButton(buttonAddWord, this->size());

        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setAlignment(Qt::AlignCenter);
        lblNameColumn->setText(QString::fromStdString(listNameColumn.at(i)));
        ui->widget->getLayoutForNameColumn()->addWidget(lblNameColumn);
        listLblNameColumn.push_back(lblNameColumn);
        GlobalFct::changeSizeFontOfLbl(lblNameColumn, this->size());

        QVBoxLayout *hboxLayoutForListWord = new QVBoxLayout;
        listVBoxLayoutForListWord.push_back(hboxLayoutForListWord);
        QLineEdit *newLineEdit = new QLineEdit;
        hboxLayoutForListWord->addWidget(newLineEdit);
        listLineEditForWord.push_back(new vector<QLineEdit*>());
        listLineEditForWord.at(i)->push_back(newLineEdit);
        GlobalFct::changeSizeFontOfLineEdit(newLineEdit, this->size());

        ui->widget->getLayoutForQLineEdit()->addLayout(hboxLayoutForListWord);

        QPushButton *buttonRemoveWord = new QPushButton;
        buttonRemoveWord->setEnabled(false);
        buttonRemoveWord->setText("-");
        ui->widget->getLayoutForRemovingBtn()->addWidget(buttonRemoveWord);
        listQPushButtonRemove.push_back(buttonRemoveWord);
        GlobalFct::changeSizeFontOfPushButton(buttonRemoveWord, this->size());

        connect(buttonAddWord, &QPushButton::clicked, this, [this, i]{addingWord(i);});
        connect(buttonRemoveWord, &QPushButton::clicked, this, [this, i]{removeWord(i);});
    }

    connect(ui->widget->getBtnAddWord(), SIGNAL(clicked()), this, SLOT(saveWord()));
    GlobalFct::changeSizeFontOfPushButton(ui->widget->getBtnAddWord(), this->size());

    finishButton = ui->widget->getConfirmBtn();
    finishButton->setText(tr("Terminer la modification du vocabulaire '%1'").arg(QString::fromStdString(nameVocab)));
    finishButton->setVisible(false);
    GlobalFct::changeSizeFontOfPushButton(finishButton, this->size());
    connect(finishButton, SIGNAL(clicked()), this, SLOT(finishVocab()));

    lblLastWord = ui->widget->getLblLastWord();
    errorInsertingWord = ui->widget->getLblError();
    GlobalFct::changeSizeFontOfLbl(lblLastWord, this->size());
    GlobalFct::changeSizeFontOfLbl(errorInsertingWord, this->size());
}

void AddWord::finishVocab(){
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

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}

void AddWord::saveWord(){
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

bool AddWord::verifyInputWord(){
    for(auto *var : listLineEditForWord){
        for(auto *lineEdit: *var){
            if(lineEdit->text() == ""){
                return false;
            }
        }
    }
    return true;
}

void AddWord::addingWord(int num){
    QLineEdit *newLineEdit = new QLineEdit;
    GlobalFct::changeSizeFontOfLineEdit(newLineEdit, this->size());
    listVBoxLayoutForListWord.at(num)->addWidget(newLineEdit);
    listLineEditForWord.at(num)->push_back(newLineEdit);

    listQPushButtonRemove.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size() == WidgetNewVocab::LIMIT_NUMBER_WORD){
        listQPushButtonAdd.at(num)->setEnabled(false);
    }
}

void AddWord::removeWord(int num){
    delete listLineEditForWord.at(num)->at(listLineEditForWord.at(num)->size()-1);
    listLineEditForWord.at(num)->erase(listLineEditForWord.at(num)->end()-1);

    listQPushButtonAdd.at(num)->setEnabled(true);
    if(listLineEditForWord.at(num)->size()==1){
        listQPushButtonRemove.at(num)->setEnabled(false);
    }
}


AddWord::~AddWord()
{
    delete ui;
}


void AddWord::resizeEvent(QResizeEvent* event){

    for(QPushButton *btn : listQPushButtonAdd){
        GlobalFct::changeSizeFontOfPushButton(btn, this->size());
    }

    for(QLabel *lbl : listLblNameColumn){
        GlobalFct::changeSizeFontOfLbl(lbl, this->size());
    }

    for(unsigned int i=0; i<listLineEditForWord.size(); i++){
        for(unsigned int j=0; j<listLineEditForWord.at(i)->size(); j++){
            GlobalFct::changeSizeFontOfLineEdit(listLineEditForWord.at(i)->at(j), this->size());
        }
    }

    for(QPushButton *btn : listQPushButtonRemove){
        GlobalFct::changeSizeFontOfPushButton(btn, this->size());
    }

    GlobalFct::changeSizeFontOfPushButton(ui->widget->getBtnAddWord(), this->size());
    GlobalFct::changeSizeFontOfPushButton(ui->widget->getConfirmBtn(), this->size());
    GlobalFct::changeSizeFontOfLbl(ui->widget->getLblLastWord(), this->size());
    GlobalFct::changeSizeFontOfLbl(ui->widget->getLblError(), this->size());

    QWidget::resizeEvent(event);
}


















