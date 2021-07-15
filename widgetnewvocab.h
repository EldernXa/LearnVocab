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

private:
    void enableEventForFirstStep();
//    void clearLayout(QLayout *layout);
//    bool verifyLineEdit();
//    bool verifyInputWord();
//    void saveColumnName();
//    void addingWord();
//    void removeWord(int num);

    QPushButton *finishBuutton = nullptr;
    vector<QLineEdit*> listLineEdit;
    vector<string> listNameColumn;
    vector<vector<QLineEdit *>> listLineEditForWord;
    vector<QVBoxLayout*> listVBoxLayoutForListWord;
    vector<QPushButton*> listQPushButtonAdd;
    vector<QPushButton*> listQPushButtonRemove;
    int numberOfColumn;
    bool addWord = false;
    string nameVocab;
    QLabel *errorLabelForNameColumn = new QLabel;
    QLabel *errorInsertingWord = nullptr;
    Ui::WidgetNewVocab *ui;
    fstream fileToSaveVocab;

    QLabel *lblLastWord = nullptr;

    const int WIDTH_LINE_EDIT_WORD = 40;
    const int HEIGHT_LINE_EDIT_WORD = 40;
    const int WIDTH_WIDGET = 250;
    const int HEIGHT_WIDGET = 20;
    const unsigned int LIMIT_NUMBER_WORD = 5;

private slots:
    void runFirstButton();
//    void valideNameColumn();
//    void saveWord();
//    void finishVocab();
};
















#endif // WIDGETNEWVOCAB_H
