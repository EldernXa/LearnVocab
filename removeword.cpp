#include "removeword.h"
#include "ui_removeword.h"

RemoveWord::RemoveWord(string nameVocab, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoveWord)
{
    ui->setupUi(this);
    this->nameVocab = nameVocab;
    readerVocab = new ReaderVocab(nameVocab);
    ui->widget->setLayout(new QVBoxLayout);
    QWidget *widgetForNameColumns = new QWidget;
    ui->widget->layout()->addWidget(widgetForNameColumns);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : readerVocab->getColumnName()){
        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        layoutForNameColumns->addWidget(lblNameColumn);
    }

    QFrame *frameVLine = new QFrame;
    ui->widget->layout()->addWidget(frameVLine);
    frameVLine->setFrameShape(QFrame::HLine);

    for(unsigned int i = 0; i<readerVocab->getAllLineOfTheVocab().size(); i++){
        vector<string> valueToDisplay = readerVocab->getLineSplited(i);
        QWidget *widgetForNameWord = new QWidget;
        ui->widget->layout()->addWidget(widgetForNameWord);
        QHBoxLayout *layoutForNameWord = new QHBoxLayout(widgetForNameWord);
        unsigned int multiply_value = 1;
        for(unsigned int j = 0; j<valueToDisplay.size(); j++){
            vector<string> differentValueForAWord = readerVocab->getWordSplitedFromLineSplited(i, j);
            if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                layoutForAWord->setSpacing(0);
                if(differentValueForAWord.size()>multiply_value){
                    multiply_value = differentValueForAWord.size();
                }

                for(auto& word: differentValueForAWord){
                    QLabel *lblNameWord = new QLabel;
                    lblNameWord->setAlignment(Qt::AlignCenter);
                    lblNameWord->setText(QString::fromStdString(word));
                    layoutForAWord->addWidget(lblNameWord);
                }
                layoutForNameWord->addWidget(widgetForAWord);
            }else{
                QLabel *lblNameWord = new QLabel;
                lblNameWord->setAlignment(Qt::AlignCenter);
                lblNameWord->setText(QString::fromStdString(valueToDisplay.at(j)));
                layoutForNameWord->addWidget(lblNameWord);
            }
        }

        layoutForNameWord->addWidget(new QCheckBox()); // TODO continue implementation checkbox.

        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        frameLine->setFrameShape(QFrame::HLine);
        QSpacerItem *itemSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->widget->layout()->addItem(itemSpacer);
    }
}

vector<string> RemoveWord::split(const string& s, char delimiter){
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

RemoveWord::~RemoveWord()
{
    delete ui;
}
