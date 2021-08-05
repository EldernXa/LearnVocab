#ifndef MODIFYWORD_H
#define MODIFYWORD_H

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

#include "readervocab.h"
#include "writervocab.h"

namespace Ui {
class ModifyWord;
}

class ModifyWord : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyWord(string nameVocab, QWidget *parent = nullptr);
    ~ModifyWord();

private slots:
    void on_buttonBack_clicked();

private:
    vector<string> split(const string&, char);

    ReaderVocab *readerVocab = nullptr;
    string nameVocab;
    QScrollArea *scrollArea;

    Ui::ModifyWord *ui;
};

#endif // MODIFYWORD_H
