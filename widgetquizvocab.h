#ifndef WIDGETQUIZVOCAB_H
#define WIDGETQUIZVOCAB_H

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <random>

#include <QWidget>
#include <QLineEdit>

#include "widgetquizvocablaststep.h"
#include "readervocab.h"

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

private:
    Ui::WidgetQuizVocab *ui;
    WidgetQuizVocabLastStep *widgetQuizLastStep;
    string nameVocab;
    int numberOfColumn;
    int randNum;
    vector<string> nameColumn;
    QVector<QVector<QVector<string>*>*> listWord;
    vector<vector<QLineEdit*>*> listLineEdit;
    int numberOfWord = 0;
    int actualWord=0;
    bool firstWord = false;

    void saveVocabWord();
    void enableEvent();
    void startingQuiz();
    void clearLayout(QLayout*, bool deleteWidgets = true);

private slots:
    void saveNumberOfWord();
    void correctVocab();
    void nextVocab();
    void finishQuiz();
};

#endif // WIDGETQUIZVOCAB_H
