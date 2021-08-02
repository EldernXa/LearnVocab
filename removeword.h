#ifndef REMOVEWORD_H
#define REMOVEWORD_H

#include <string>

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>

#include "readervocab.h"
#include "writervocab.h"

using namespace std;

namespace Ui {
class RemoveWord;
}

class RemoveWord : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveWord(string, QWidget *parent = nullptr);
    ~RemoveWord();

private slots:
    void on_pushButton_clicked();

    void on_validRemoveButton_clicked();

private:
    vector<string> split(const string&, char delimiter);

    ReaderVocab *readerVocab = nullptr;
    string nameVocab;
    QScrollArea *scrollArea;
    vector<QCheckBox *> listCheckBox;

    Ui::RemoveWord *ui;
};

#endif // REMOVEWORD_H


















