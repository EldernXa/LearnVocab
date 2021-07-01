#include "displayvocab.h"

DisplayVocab::DisplayVocab(std::string nameVocab, QWidget *parent) : QMainWindow(parent)
{
    nameVocabToDisplay = nameVocab;
    scrollArea = new QScrollArea(this);
    //this->setCentralWidget(scrollArea);
    QWidget *scrollAreaContent = new QWidget;
    //scrollAreaContent->setLayout(new QVBoxLayout);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollAreaContent);
    //scrollArea->setFixedHeight(this->size().height());
    //scrollArea->setFixedWidth(this->size().width());

    fileToDisplayVocab.open(nameVocab+".vocab", ios::in);
    string value;
    getline(fileToDisplayVocab, value);
    numberOfColumn = stoi(value);
    getline(fileToDisplayVocab, value);
    nameColumns = split(value, ';');

    this->resize(numberOfColumn*WIDTH_LABEL + WIDTH_LABEL, 400);

    QWidget *widgetForNameColumns = new QWidget(scrollAreaContent);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : nameColumns){
        QLabel *lblNameColumn = new QLabel();
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setAlignment(Qt::AlignCenter);
        lblNameColumn->setFixedHeight(HEIGHT_LABEL);
        lblNameColumn->setFixedWidth(WIDTH_LABEL);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    lastHeight += HEIGHT_LABEL+1;
    QFrame *frameVLine = new QFrame(scrollAreaContent);
    frameVLine->setFixedWidth(numberOfColumn*WIDTH_LABEL);
    frameVLine->setFrameShape(QFrame::HLine);
    frameVLine->move(0, lastHeight);
    while(getline(fileToDisplayVocab, value)){
        vector<string> valueToDisplay = split(value, ';');
        QWidget *widgetForNameWord = new QWidget(scrollAreaContent);
        QHBoxLayout *layoutForNameWord = new QHBoxLayout(widgetForNameWord);
        widgetForNameWord->move(0, lastHeight);
        unsigned int multiply_value=1;
        for(auto &nameWord : valueToDisplay){
            vector<string> differentValueForAWord = split(nameWord, ',');
            if(differentValueForAWord.size()>1){
                QWidget *widgetForAWord = new QWidget;
                QVBoxLayout *layoutForAWord = new QVBoxLayout(widgetForAWord);
                layoutForAWord->setSpacing(0);
                if(differentValueForAWord.size()>multiply_value){
                    multiply_value = differentValueForAWord.size();
                }
                for(auto &word : differentValueForAWord){
                    QLabel *lblNameWord = new QLabel;
                    lblNameWord->setAlignment(Qt::AlignCenter);
                    lblNameWord->setText(QString::fromStdString(word));
                    lblNameWord->setFixedHeight(HEIGHT_LABEL);
                    lblNameWord->setFixedWidth(WIDTH_LABEL);
                    layoutForAWord->addWidget(lblNameWord);
                }
                layoutForNameWord->addWidget(widgetForAWord);
            }else{
                QLabel *lblNameWord = new QLabel;
                lblNameWord->setAlignment(Qt::AlignCenter);
                lblNameWord->setText(QString::fromStdString(nameWord));
                lblNameWord->setFixedHeight(HEIGHT_LABEL);
                lblNameWord->setFixedWidth(WIDTH_LABEL);
                layoutForNameWord->addWidget(lblNameWord);
            }
        }
        lastHeight+=(HEIGHT_LABEL*multiply_value);
        QFrame *frameLine = new QFrame(scrollAreaContent);
        frameLine->setFixedWidth(numberOfColumn*WIDTH_LABEL);
        frameLine->setFrameShape(QFrame::HLine);
        frameLine->move(0, lastHeight);
    }
    fileToDisplayVocab.close();
}

void DisplayVocab::resizeEvent(QResizeEvent *qresizeEvent){
    // TODO fix the ratio of the scroll
    // TODO change the variables uses here.
    scrollArea->setFixedHeight(this->height());
    scrollArea->setFixedWidth(this->width());
    scrollArea->widget()->setFixedHeight(this->height()+lastHeight);
    scrollArea->widget()->setFixedWidth(this->width());
    QWidget::resizeEvent(qresizeEvent);
}

std::vector<std::string> DisplayVocab::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}












