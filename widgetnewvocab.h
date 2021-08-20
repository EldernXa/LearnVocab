#ifndef WIDGETNEWVOCAB_H
#define WIDGETNEWVOCAB_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

#include <QWidget>
#include <QRect>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

#include "widgetnewvocabsecondstep.h"
#include "widgetnewvocablaststep.h"
#include "ModifyVocab/writervocab.h"
#include "CstFile/globalfct.h"

using namespace std;

namespace Ui {
class WidgetNewVocab;
}

class WidgetNewVocab : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewVocab(QWidget *parent = nullptr);
    ~WidgetNewVocab();

    static const unsigned int LIMIT_NUMBER_WORD = 5;

protected:
    void resizeEvent(QResizeEvent*);

private:
    enum StepNewVocab{initStep, secondStep, lastStep};
    void enableEventForFirstStep();
    void clearLayout(QLayout *layout, bool deleteWidgets = true);
    bool verifLineEdit();
    bool verifyInputWord();
    void saveColumnName();
    void addingWord(int num);
    void removeWord(int num);
    void startLastStep();

    QPushButton *finishButton = nullptr;
    vector<QLineEdit*> listLineEdit;
    vector<string> listNameColumn;
    vector<vector<QLineEdit *>*> listLineEditForWord;
    vector<QVBoxLayout*> listVBoxLayoutForListWord;
    vector<QPushButton*> listQPushButtonAdd;
    vector<QPushButton*> listQPushButtonRemove;
    int numberOfColumn;
    bool addWord = false;
    string nameVocab;
    QLabel *errorLabelForNameColumn = new QLabel;
    QLabel *errorInsertingWord = nullptr;
    Ui::WidgetNewVocab *ui;
    WriterVocab *writerVocab = nullptr;
    //fstream fileToSaveVocab;

    QLabel *lblLastWord = nullptr;

    StepNewVocab step = initStep;

    const int WIDTH_LINE_EDIT_WORD = 40;
    const int HEIGHT_LINE_EDIT_WORD = 40;
    const int WIDTH_WIDGET = 250;
    const int HEIGHT_WIDGET = 20;

private slots:
    void runFirstButton();
    void valideNameColumn();
    void saveWord();
    void finishVocab();
};
















#endif // WIDGETNEWVOCAB_H
