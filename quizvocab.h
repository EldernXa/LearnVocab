#ifndef QUIZVOCAB_H
#define QUIZVOCAB_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <algorithm>
#include <random>

#include <QMainWindow>

using namespace std;

namespace Ui {
class QuizVocab;
}

class QuizVocab : public QMainWindow
{
    Q_OBJECT

public:
    enum QuizType {randomNWord, NFirstwordNotKnow};
    explicit QuizVocab(std::string, QuizType, QWidget *parent = nullptr);
    ~QuizVocab();

private:
    Ui::QuizVocab *ui;
    std::string nameVocab;
    int numberOfColumn;
    vector<string> nameColumn;
    QVector<QVector<QVector<string>*>*> listWord;
    int numberOfWord;

    void saveVocabWord();
    void enableEvent();

private slots:
    void saveNumberOfWord();
};

#endif // QUIZVOCAB_H
