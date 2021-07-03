#ifndef QUIZVOCAB_H
#define QUIZVOCAB_H

#include <iostream>

#include <QMainWindow>

using namespace std;

namespace Ui {
class QuizVocab;
}

class QuizVocab : public QMainWindow
{
    Q_OBJECT

public:
    enum QuizType {randomNWord};
    explicit QuizVocab(std::string, QuizType, QWidget *parent = nullptr);
    ~QuizVocab();

private:
    Ui::QuizVocab *ui;
    std::string nameVocab;
    int numberOfColumn;
    vector<string> nameColumn;
};

#endif // QUIZVOCAB_H
