#ifndef DISPLAYVOCAB_H
#define DISPLAYVOCAB_H

#include <fstream>
#include <iostream>

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>

using namespace std;


class DisplayVocab : public QMainWindow
{
    Q_OBJECT
public:
    explicit DisplayVocab(std::string nameVocab, QWidget *parent = nullptr);


private:
    string nameVocabToDisplay;
    int numberOfColumn;

    fstream fileToDisplayVocab;

    QScrollArea *scrollArea;

signals:

};

#endif // DISPLAYVOCAB_H
