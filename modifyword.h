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
#include <QPushButton>

#include "ModifyVocab/readervocab.h"
#include "ModifyVocab/writervocab.h"
#include "CstFile/globalfct.h"

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
    void on_buttonConfirmModify_clicked();
    void deletingWord(int);
    void changeStateWord(int);

protected:
    void resizeEvent(QResizeEvent*);

private:
    vector<string> split(const string&, char);
    void setDeleteIcon(QPushButton*);
    void setGreenCheckIcon(QPushButton*);
    void setRedCrossIcon(QPushButton*);
    void clearLayout(QLayout*, bool deleteWidgets = true);

    ReaderVocab *readerVocab = nullptr;
    string nameVocab;
    QScrollArea *scrollArea;
    vector<bool> listIsKnown;
    vector<QPushButton*> listButtonChangeState;
    vector<vector<vector<QLineEdit*>>> listLineEditForWord;
    vector<QHBoxLayout*> listLayout;
    vector<QFrame*> listHLine;
    vector<QWidget*> listWidget;
    vector<int> listIndToDelete;

    vector<QLabel*> listLblNameColumn;
    vector<QPushButton*> listButtonForWord;

    Ui::ModifyWord *ui;
};

#endif // MODIFYWORD_H


















