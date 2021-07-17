#ifndef WIDGETQUIZVOCAB_H
#define WIDGETQUIZVOCAB_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <algorithm>
#include <random>

#include <QWidget>
#include <QLineEdit>

#include "widgetquizvocablaststep.h"

using namespace std;

namespace Ui {
class WidgetQuizVocab;
}

class WidgetQuizVocab : public QWidget
{
    Q_OBJECT

public:
    enum QuizType {randomNWord, NFirstWordNotKnow};
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

    void saveVocabWord();
    void enableEvent();
    void startingQuiz();
    void clearLayout(QLayout*, bool deleteWidgets = true);

private slots:
    void saveNumberOfWord();
    void correctVocab();
};

#endif // WIDGETQUIZVOCAB_H
