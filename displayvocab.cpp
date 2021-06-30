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
    scrollArea->setFixedHeight(this->size().height());
    scrollArea->setFixedWidth(this->size().width());

    fileToDisplayVocab.open(nameVocab+".vocab", ios::in);
    string value;
    getline(fileToDisplayVocab, value);
    numberOfColumn = stoi(value);
    getline(fileToDisplayVocab, value);
    nameColumns = split(value, ';');

    QWidget *widgetForNameColumns = new QWidget(scrollAreaContent);
    QHBoxLayout *layoutForNameColumns = new QHBoxLayout(widgetForNameColumns);
    for(auto &nameColumn : nameColumns){
        QLabel *lblNameColumn = new QLabel();
        lblNameColumn->setText(QString::fromStdString(nameColumn));
        lblNameColumn->setFixedHeight(HEIGHT_LABEL);
        lblNameColumn->setFixedWidth(WIDTH_LABEL);
        layoutForNameColumns->addWidget(lblNameColumn);
    }
    //scrollAreaContent->layout()->addWidget(widgetForNameColumns);
    fileToDisplayVocab.close();
}

void DisplayVocab::resizeEvent(QResizeEvent *qresizeEvent){
    scrollArea->setFixedHeight(this->height());
    scrollArea->setFixedWidth(this->width());
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












