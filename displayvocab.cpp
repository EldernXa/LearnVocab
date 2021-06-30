#include "displayvocab.h"

DisplayVocab::DisplayVocab(std::string nameVocab, QWidget *parent) : QMainWindow(parent)
{
    nameVocabToDisplay = nameVocab;
    scrollArea = new QScrollArea(this);
    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(new QVBoxLayout);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollAreaContent);

    fileToDisplayVocab.open(nameVocab+".vocab", ios::in);
    string value;
    getline(fileToDisplayVocab, value);
    numberOfColumn = stoi(value);
    cout << numberOfColumn << endl;
    fileToDisplayVocab.close();
}












