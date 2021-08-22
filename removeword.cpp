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
        listLblNameColumn.push_back(lblNameColumn);
        GlobalFct::changeSizeFontOfLbl(lblNameColumn, this->size());
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    QLabel *newlbl = new QLabel;
    layoutForNameColumns->addWidget(newlbl);
    GlobalFct::changeSizeFontOfLbl(newlbl, this->size());
    listLblNameColumn.push_back(newlbl);

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
                    listLblWord.push_back(lblNameWord);
                    GlobalFct::changeSizeFontOfLbl(lblNameWord, this->size());
                }
                layoutForNameWord->addWidget(widgetForAWord);
            }else{
                QLabel *lblNameWord = new QLabel;
                lblNameWord->setAlignment(Qt::AlignCenter);
                lblNameWord->setText(QString::fromStdString(valueToDisplay.at(j)));
                layoutForNameWord->addWidget(lblNameWord);
                listLblWord.push_back(lblNameWord);
                GlobalFct::changeSizeFontOfLbl(lblNameWord, this->size());
            }
        }

        QCheckBox *newCheckBox = new QCheckBox;
        layoutForNameWord->addWidget(newCheckBox);
        listCheckBox.push_back(newCheckBox);

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

void RemoveWord::on_pushButton_clicked()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}


void RemoveWord::on_validRemoveButton_clicked()
{
    vector<int> listIndWhoAreDeleted;
    for(unsigned int i=0; i<listCheckBox.size(); i++){
        if(listCheckBox.at(i)->isChecked()){
            listIndWhoAreDeleted.push_back(i);
        }
    }
    WriterVocab *writerVocab = new WriterVocab(nameVocab, listIndWhoAreDeleted);
    writerVocab->close();
    clearLayout(ui->widget->layout());
    listCheckBox.clear();

    readerVocab = new ReaderVocab(nameVocab);
    QWidget *widgetForNameColumns = new QWidget;
    ui->widget->layout()->addWidget(widgetForNameColumns);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : readerVocab->getColumnName()){
        QLabel *lblNameColumn = new QLabel;
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    layoutForNameColumns->addWidget(new QLabel);

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

        QCheckBox *newCheckBox = new QCheckBox;
        layoutForNameWord->addWidget(newCheckBox);
        listCheckBox.push_back(newCheckBox);

        QFrame *frameLine = new QFrame;
        ui->widget->layout()->addWidget(frameLine);
        frameLine->setFrameShape(QFrame::HLine);
        QSpacerItem *itemSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->widget->layout()->addItem(itemSpacer);
    }
}

void RemoveWord::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void RemoveWord::resizeEvent(QResizeEvent *event){

    for(QLabel *lbl : listLblNameColumn){
        GlobalFct::changeSizeFontOfLbl(lbl, this->size());
    }

    for(QLabel *lbl : listLblWord){
        GlobalFct::changeSizeFontOfLbl(lbl, this->size());
    }

    GlobalFct::changeSizeFontOfPushButton(ui->validRemoveButton, this->size());
    GlobalFct::changeSizeFontOfPushButton(ui->pushButton, this->size());

    QWidget::resizeEvent(event);
}


















