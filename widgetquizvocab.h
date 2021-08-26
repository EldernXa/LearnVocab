#ifndef WIDGETQUIZVOCAB_H
#define WIDGETQUIZVOCAB_H

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <random>

#include <QWidget>
#include <QLineEdit>
#include <QScreen>
#include <QKeyEvent>
#include <QEvent>
#include <QTimer>

#include "widgetquizvocablaststep.h"
#include "ModifyVocab/readervocab.h"
#include "CstFile/globalfct.h"

using namespace std;

namespace Ui {
class WidgetQuizVocab;
}

class WidgetQuizVocab : public QWidget
{
    Q_OBJECT

public:
    enum QuizType {randomNWord, NRandomWordNotKnow, NRandomWordKnow, NFirstWordNotKnow, NFirstWordKnow};
    explicit WidgetQuizVocab(string, QuizType, QWidget *parent = nullptr);
    ~WidgetQuizVocab();

protected:
    void resizeEvent(QResizeEvent*);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::WidgetQuizVocab *ui;
    WidgetQuizVocabLastStep *widgetQuizLastStep = nullptr;
    string nameVocab;
    int numberOfColumn;
    int randNum;
    vector<string> nameColumn;
    QVector<QVector<QVector<string>*>*> listWord;
    vector<vector<QLineEdit*>*> listLineEdit;
    vector<QLabel*> listLbl;
    int numberOfWord = 0;
    int actualWord=0;
    bool firstWord = false;
    bool isFirstStep = true;
    bool enterIsPressed = false;
    bool verifRand;

    void enableEvent();
    void startingQuiz();
    void clearLayout(QLayout*, bool deleteWidgets = true);
    QVBoxLayout* getLayoutForCorrectVocab(int);
    //int getNewSizeFont();

private slots:
    void saveNumberOfWord();
    void correctVocab();
    void nextVocab();
    void finishQuiz();
};

#endif // WIDGETQUIZVOCAB_H
