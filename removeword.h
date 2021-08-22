#ifndef REMOVEWORD_H
#define REMOVEWORD_H

#include <string>

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>

#include "ModifyVocab/readervocab.h"
#include "ModifyVocab/writervocab.h"
#include "CstFile/globalfct.h"

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

protected:
    void resizeEvent(QResizeEvent*);

private:
    vector<string> split(const string&, char delimiter);
    void clearLayout(QLayout*, bool = true);
    vector<QLabel*> listLblNameColumn;
    vector<QLabel*> listLblWord;

    ReaderVocab *readerVocab = nullptr;
    string nameVocab;
    QScrollArea *scrollArea;
    vector<QCheckBox *> listCheckBox;

    Ui::RemoveWord *ui;
};

#endif // REMOVEWORD_H


















