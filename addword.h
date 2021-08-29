#ifndef ADDWORD_H
#define ADDWORD_H

#include <string>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTimer>

#include "ModifyVocab/readervocab.h"
#include "ModifyVocab/writervocab.h"
#include "CstFile/globalfct.h"
#include "CstFile/cststatic.h"

using namespace std;

namespace Ui {
class AddWord;
}

class AddWord : public QWidget
{
    Q_OBJECT

public:
    explicit AddWord(string, QWidget *parent = nullptr);
    ~AddWord();

private:
    void addingWord(int);
    void removeWord(int);
    bool verifyInputWord();

    Ui::AddWord *ui;
    string nameVocab;
    QPushButton *finishButton;
    vector<QPushButton*> listQPushButtonAdd;
    vector<QPushButton*> listQPushButtonRemove;
    vector<QVBoxLayout*> listVBoxLayoutForListWord;
    vector<vector<QLineEdit*>*> listLineEditForWord;
    QLabel* lblLastWord;
    QLabel* errorInsertingWord;
    WriterVocab *writerVocab = nullptr;

    vector<QLabel*> listLblNameColumn;

    bool keyIsAlreadyClicked = false;

protected:
    void resizeEvent(QResizeEvent*);
    bool eventFilter(QObject*, QEvent*);

private slots:
    void saveWord();
    void finishVocab();
};

#endif // ADDWORD_H
